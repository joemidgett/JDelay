// AudioDelayParameters.h

#pragma once

#include <math.h>
#include <memory>
#include <time.h>

#include <JuceHeader.h>

#include "DSPUtils.h"

/**
\struct AudioDelayParameters
\ingroup FX-Objects
\brief
Custom parameter structure for the AudioDelay object.

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
struct AudioDelayParameters
{
    AudioDelayParameters() {}
    /** all FXObjects parameter objects require overloaded= operator so remember to add new entries if you add new variables. */
    AudioDelayParameters& operator=(const AudioDelayParameters& params)	// need this override for collections to work
    {
        if (this == &params)
            return *this;

        algorithm = params.algorithm;
        wetLevel_dB = params.wetLevel_dB;
        dryLevel_dB = params.dryLevel_dB;
        feedback_Pct = params.feedback_Pct;

        updateType = params.updateType;
        leftDelay_mSec = params.leftDelay_mSec;
        rightDelay_mSec = params.rightDelay_mSec;
        delayRatio_Pct = params.delayRatio_Pct;

        return *this;
    }

    // --- individual parameters
    delayAlgorithm algorithm = delayAlgorithm::kNormal; ///< delay algorithm
    double wetLevel_dB = -3.0;	///< wet output level in dB
    double dryLevel_dB = -3.0;	///< dry output level in dB
    double feedback_Pct = 0.0;	///< feedback as a % value

    delayUpdateType updateType = delayUpdateType::kLeftAndRight;///< update algorithm
    double leftDelay_mSec = 0.0;	///< left delay time
    double rightDelay_mSec = 0.0;	///< right delay time
    double delayRatio_Pct = 100.0;	///< dela ratio: right length = (delayRatio)*(left length)
};