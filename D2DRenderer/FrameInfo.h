#pragma once

struct FrameInfo
{
	int left;
	int top;
	int right;
	int bottom;

	/// TO DO: 여기에 애니메이션 재생 속도? 변수 추가하기
	FrameInfo(int _left, int _top, int width, int height)
		: left(_left)
		, top(_top)
		, right(_left + width)
		, bottom(top + height)
	{

	}
};