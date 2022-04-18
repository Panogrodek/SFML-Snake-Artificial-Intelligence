#include "stdafx.h"
#include "DeltaTime.hpp"
DeltaTime DeltaTime::s_instance;

DeltaTime::DeltaTime()
{
	m_DeltaTimeClock.restart();
}

DeltaTime::~DeltaTime()
{
}
