#pragma once


struct exColor;

class ColorHandle
{
public:
	ColorHandle(exColor* color);

	bool isValid() const;

	exColor* GetColor() const;

private:
	exColor* mExColor;
};