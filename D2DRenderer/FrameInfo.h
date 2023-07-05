#pragma once

struct FrameInfo
{
	int left;
	int top;
	int right;
	int bottom;

	/// TO DO: ���⿡ �ִϸ��̼� ��� �ӵ�? ���� �߰��ϱ�
	FrameInfo(int _left, int _top, int width, int height)
		: left(_left)
		, top(_top)
		, right(_left + width)
		, bottom(top + height)
	{

	}
};