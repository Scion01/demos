
//////////////////////////////////////////////////////////////////
//
//  Arturo Cepeda Pérez
//  iOS Game Engine
//
//  Sample application
//
//  --- AppDelegate.m ---
//
//////////////////////////////////////////////////////////////////

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;

-(void) dealloc
{
   [_window release];
   [super dealloc];
}

-(BOOL) application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    return YES;
}
							
-(void) applicationWillResignActive:(UIApplication*)application
{
}

-(void) applicationDidEnterBackground:(UIApplication*)application
{
}

-(void) applicationWillEnterForeground:(UIApplication*)application
{
}

-(void) applicationDidBecomeActive:(UIApplication*)application
{
}

-(void) applicationWillTerminate:(UIApplication*)application
{
}

@end
