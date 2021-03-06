/*========================================================
* CInterpolatorVec3Base.cpp
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#include "CInterpolatorVec3Base.h"
#include <math.h>

namespace Time
{

	//////////////////////////////////////////////////////////////////////////

	CInterpolatorVec3Base::CInterpolatorVec3Base()
		: mTimeMode(TIME_CLAMP)
	{

	}

	//////////////////////////////////////////////////////////////////////////

	CInterpolatorVec3Base::~CInterpolatorVec3Base()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorVec3Base::SetKeyframes(const Time::SKeyframeVec3 *frames, size_t n)
	{
		mKeyframes.resize(n);
		memcpy(&mKeyframes[0], frames, sizeof(SKeyframeVec3) * n);
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorVec3Base::ClearKeyframes()
	{
		mKeyframes.clear();
	}
	
	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorVec3Base::AddKeyframe(const Time::SKeyframeVec3 &pnt)
	{
		mKeyframes.push_back(pnt);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CInterpolatorVec3Base::findSegment(float t) const
	{
		// Binary search
		int l = 0, r = (int)mKeyframes.size() - 1, m;

		while(l != r - 1)
		{
			m = (l + r) / 2;
			if( mKeyframes[m].time >= t )
				r = m;
			else
				l = m;
		}

		return l;
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorVec3Base::processTime(float &t) const
	{
		if(t >= 0.0f && t <= 1.0f) return;

		switch(mTimeMode)
		{
		case TIME_CLAMP:
			t = t > 1.0f ? 1.0f : 0.0f;
			break;

		case TIME_WRAP:
			t = t - floor(t);
			break;

		case TIME_MIRROR:
			{
				float f = floor(t);
				t -= f;
				int i = (int)f % 2;
				t = i ? 1.0f - t : t;
			}
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace