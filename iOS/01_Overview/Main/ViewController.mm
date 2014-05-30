
//////////////////////////////////////////////////////////////////
//
//  Arturo Cepeda Pérez
//  iOS Game Engine
//
//  Sample application
//
//  --- ViewController.mm ---
//
//////////////////////////////////////////////////////////////////


#import "ViewController.h"

#import "GERenderingES20.h"
#import "GEAudioOpenAL.h"
#import "GEScene.h"
#import "GETimer.h"

#import "SceneSample.h"


@interface ViewController () <UIAccelerometerDelegate>
{
   // Rendering system
   GERendering* cRender;
   
   // Audio system
   GEAudio* cAudio;
   
   // Scene management
   GEScene* cScenes[NUM_SCENES];
   int iCurrentScene;
   
   // Input management
   int iFingerID[MAX_FINGERS];
   UIAccelerometer* uiAccel;
   
   // Timer
   GETimer cTimer;
   double dTime;
}

@property (strong, nonatomic) EAGLContext* context;
@property (strong, nonatomic) GLKBaseEffect* effect;

-(void) accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration;
-(void) selectScene:(unsigned int) iScene;

@end


@implementation ViewController

@synthesize context = _context;
@synthesize effect = _effect;

-(void) dealloc
{
   [_context release];
   [_effect release];
   [super dealloc];
}

-(void) viewDidLoad
{
   [super viewDidLoad];

   // initialize OpenGL
   self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

   if(!self.context) 
       NSLog(@"Failed to create ES context");
    
   GLKView* view = (GLKView*)self.view;
   view.context = self.context;
   view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

   [EAGLContext setCurrentContext:self.context];
   
   // set frames per second
   self.preferredFramesPerSecond = FPS;
   
   // enable multiple touch
   self.view.userInteractionEnabled = YES;
   self.view.multipleTouchEnabled = YES;
   self.view.exclusiveTouch = YES;
   
   // IDs for touch management
   for(int i = 0; i < MAX_FINGERS; i++)
      iFingerID[i] = 0;
   
#ifdef USE_ACCELEROMETER
   // accelerometer
   uiAccel = [UIAccelerometer sharedAccelerometer];
   uiAccel.updateInterval = ACCELEROMETER_UPDATE;
   uiAccel.delegate = self;
#endif
   
   // initialize rendering system
   cRender = new GERenderingES20();
   cRender->setBackgroundColor(GEColor(0.5f, 0.5f, 1.0f));
   
   // initialize audio system
   cAudio = new GEAudioOpenAL();
   cAudio->init();
   
   // create scenes
   cScenes[0] = (GEScene*)new GESceneSample(cRender, cAudio, NULL);
   // ...
   // ...
   
   // start the timer
   cTimer.start();
   dTime = 0.0;
   
   // select the first scene   
   iCurrentScene = 0;
   cScenes[0]->init();
}

-(void) viewDidUnload
{    
   [super viewDidUnload];
   
   [EAGLContext setCurrentContext:self.context];
    
   if([EAGLContext currentContext] == self.context) 
      [EAGLContext setCurrentContext:nil];

   self.context = nil;
   
   // release rendering system
   delete cRender;
   
   // release audio system
   cAudio->release();
   delete cAudio;
}

-(void) didReceiveMemoryWarning
{
   [super didReceiveMemoryWarning];
}

-(BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
#ifdef PORTRAIT_UP
   if(interfaceOrientation == UIInterfaceOrientationPortrait)
      return YES;
#endif
#ifdef PORTRAIT_DOWN
   if(interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
      return YES;
#endif
#ifdef LANDSCAPE_HOME_LEFT
   if(interfaceOrientation == UIInterfaceOrientationLandscapeRight)
      return YES;
#endif
#ifdef LANDSCAPE_HOME_RIGHT
   if(interfaceOrientation == UIInterfaceOrientationLandscapeLeft)
      return YES;
#endif   
   
   return NO;
}

-(void) accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{
   cScenes[iCurrentScene]->updateAccelerometerStatus(GEVector3(acceleration.x, acceleration.y, acceleration.z));
}

-(void) selectScene:(unsigned int)iScene
{
   cScenes[iCurrentScene]->release();
   iCurrentScene = iScene;
   cScenes[iCurrentScene]->init();
}

-(void) update
{
   // delta time
   double dCurrentTime = cTimer.getTime();
   float fDeltaTime = (dCurrentTime - dTime) * 0.001f;
   dTime = dCurrentTime;
   
   // update
   cScenes[iCurrentScene]->update(fDeltaTime);
    
   // scene change request
   if(cScenes[iCurrentScene]->getNextScene() >= 0)
      [self selectScene:cScenes[iCurrentScene]->getNextScene()];
}

-(void) glkView:(GLKView *)view drawInRect:(CGRect)rect
{
   cRender->renderBegin();
   cScenes[iCurrentScene]->render();
   [self.context presentRenderbuffer:GL_RENDERBUFFER];
}

-(void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
   NSArray* uiTouchesList = [touches allObjects];
   
   for(UITouch* uiTouch in uiTouchesList)
   {
      for(int i = 0; i < MAX_FINGERS; i++)
      {
         if(iFingerID[i] == 0)
         {
            CGPoint cgPoint = [uiTouch locationInView: self.view];
            
            iFingerID[i] = (int)uiTouch;
            cScenes[iCurrentScene]->inputTouchBegin(i, GEVector2(cgPoint.x, cgPoint.y));
            
            break;
         }
      }
   }
}

-(void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
   NSArray* uiTouchesList = [touches allObjects];   
   
   for(UITouch* uiTouch in uiTouchesList)
   {
      for(int i = 0; i < MAX_FINGERS; i++)
      {
         if(iFingerID[i] == (int)uiTouch)
         {
            CGPoint cgPreviousPoint = [uiTouch previousLocationInView: self.view];
            CGPoint cgCurrentPoint = [uiTouch locationInView: self.view];
            
            cScenes[iCurrentScene]->inputTouchMove(i,
                                                   GEVector2(cgPreviousPoint.x, cgPreviousPoint.y),
                                                   GEVector2(cgCurrentPoint.x, cgCurrentPoint.y));            
            break;
         }
      }
   }   
}

-(void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
   NSArray* uiTouchesList = [touches allObjects];
   
   for(UITouch* uiTouch in uiTouchesList)
   {
      for(int i = 0; i < MAX_FINGERS; i++)
      {
         if(iFingerID[i] == (int)uiTouch)
         {
            CGPoint cgPoint = [uiTouch locationInView: self.view];
            
            iFingerID[i] = 0;
            cScenes[iCurrentScene]->inputTouchEnd(i, GEVector2(cgPoint.x, cgPoint.y));
            
            break;
         }
      }
   }
}

-(void) touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
   [self touchesEnded:touches withEvent:event];
}

@end
