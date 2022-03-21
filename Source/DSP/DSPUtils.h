// DSPUtils.h

#pragma once

#include <math.h>
#include <memory>
#include <time.h>

#include <JuceHeader.h>

/**
@convertIntToEnum
\ingroup ASPiK-GUI
\def convertIntToEnum
@brief convert an int to an enum, e.g. for passing to functions
\param INT - the int to compare with
\param ENUM - the typed enum to compare with
\return the int value properly cast as the enum type
*/
#define convertIntToEnum(INT,ENUM) static_cast<ENUM>(INT)

/**
@boundValue
\ingroup FX-Functions

@brief  Bound a value to min and max limits

\param value - value to bound
\param minValue - lower bound limit
\param maxValue - upper bound limit
*/
inline void boundValue(double& value, double minValue, double maxValue)
{
    value = fmin(value, maxValue);
    value = fmax(value, minValue);
}

/**
\enum delayAlgorithm
\ingroup Constants-Enums
\brief
Use this strongly typed enum to easily set the delay algorithm

- enum class delayAlgorithm { kNormal, kPingPong };

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
enum class delayAlgorithm { kNormal, kPingPong };

/**
\enum delayUpdateType
\ingroup Constants-Enums
\brief
Use this strongly typed enum to easily set the delay update type; this varies depending on the designer's choice
of GUI controls. See the book reference for more details.

- enum class delayUpdateType { kLeftAndRight, kLeftPlusRatio };

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
enum class delayUpdateType { kLeftAndRight, kLeftPlusRatio };

/**
@doLinearInterpolation
\ingroup FX-Functions

@brief performs linear interpolation of fractional x distance between two adjacent (x,y) points;
returns interpolated value

\param y1 - the y coordinate of the first point
\param y2 - the 2 coordinate of the second point
\param x - the interpolation location as a fractional distance between x1 and x2 (which are not needed)
\return the interpolated value or y2 if the interpolation is outside the x interval
*/
inline double doLinearInterpolation(double y1, double y2, double fractional_X)
{
    // --- check invalid condition
    if (fractional_X >= 1.0) return y2;

    // --- use weighted sum method of interpolating
    return fractional_X * y2 + (1.0 - fractional_X) * y1;
}