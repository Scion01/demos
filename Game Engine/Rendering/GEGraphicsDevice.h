
//////////////////////////////////////////////////////////////////
//
//  Arturo Cepeda P�rez
//  Game Engine
//
//  Rendering
//
//  --- GEGraphicsDevice.h ---
//
//////////////////////////////////////////////////////////////////

#pragma once

class GEGraphicsDevice
{
public:
    GEGraphicsDevice();
    virtual ~GEGraphicsDevice();

    virtual void* getNativePointer() = 0;
};
