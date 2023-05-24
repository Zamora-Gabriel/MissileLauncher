#include "ColorHandler.h"

ColorHandle::ColorHandle(exColor* color)
	: mExColor(color)
{}

bool ColorHandle::isValid() const
{
	return mExColor != nullptr;
}

exColor* ColorHandle::GetColor() const
{
	return mExColor;
}