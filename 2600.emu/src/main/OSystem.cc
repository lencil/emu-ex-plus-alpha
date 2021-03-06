/*  This file is part of 2600.emu.

	2600.emu is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	2600.emu is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with 2600.emu.  If not, see <http://www.gnu.org/licenses/> */

#include <OSystem.hxx>
#include <FrameBuffer.hxx>
#include <EventHandler.hxx>
#include <stella/emucore/Console.hxx>
#include <stella/emucore/PropsSet.hxx>
#include <stella/common/StateManager.hxx>
#include <stella/emucore/Random.hxx>
#include <stella/emucore/SerialPort.hxx>
#include <stella/emucore/Settings.hxx>
#include "SoundGeneric.hh"
// TODO: Some Stella types collide with MacTypes.h
#define BytePtr BytePtrMac
#define Debugger DebuggerMac
#include <imagine/time/Time.hh>
#include <imagine/logger/logger.h>
#include <emuframework/EmuSystem.hh>
#undef BytePtr
#undef Debugger

OSystem::OSystem()
{
	mySettings = std::make_unique<Settings>(*this);
	myRandom = std::make_unique<Random>(*this);
	myFrameBuffer = std::make_unique<FrameBuffer>();
	myEventHandler = std::make_unique<EventHandler>(*this);
	myPropSet = std::make_unique<PropertiesSet>("");
	myStateManager = std::make_unique<StateManager>(*this);
	mySerialPort = std::make_unique<SerialPort>();
	mySound = std::make_unique<SoundGeneric>(*this);
}

EventHandler& OSystem::eventHandler() const
{
	return *myEventHandler;
}

Random& OSystem::random() const
{
	return *myRandom;
}

FrameBuffer& OSystem::frameBuffer() const
{
	return *myFrameBuffer;
}

Sound& OSystem::sound() const
{
	return *mySound;
}

SoundGeneric& OSystem::soundGeneric() const
{
	return *mySound;
}

Settings& OSystem::settings() const
{
	return *mySettings;
}

PropertiesSet& OSystem::propSet() const
{
	return *myPropSet;
}

SerialPort& OSystem::serialPort() const
{
	return *mySerialPort;
}

StateManager& OSystem::state() const
{
	return *myStateManager;
}

void OSystem::makeConsole(unique_ptr<Cartridge>& cart, const Properties& props)
{
	myConsole = std::make_unique<Console>(*this, cart, props);
}

void OSystem::deleteConsole()
{
	myConsole = {};
}

std::string OSystem::stateDir() const
{
	return EmuSystem::savePath();
}

std::string OSystem::nvramDir() const
{
	return EmuSystem::savePath();
}

void OSystem::logMessage(const string& message, uInt8 level)
{
	if(Config::DEBUG_BUILD)
		logMsg("%s", message.c_str());
}

uInt64 OSystem::getTicks() const
{
	return IG::Time::now().uSecs();
}
