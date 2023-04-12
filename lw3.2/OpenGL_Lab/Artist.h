#include "glew.h"
#include "glfw3.h"
#include <corecrt_math_defines.h>
#include <stdexcept>
#include <chrono>

class Artist
{
public:
	Artist(int w, int h)
	{
		m_window_width = w;
		m_window_height = h;
	}

	void OnRunStart();

	void Draw(std::chrono::steady_clock::time_point m_startTime, int width, int height) const;

	std::chrono::steady_clock::time_point m_startTime;

private:
	int m_window_width = 0;
	int m_window_height = 0;
	float m_rgb_gray = 0.70588235294f;
	float m_rgb_black = 0;
	float m_rgb_white= 1;

	static void SetupProjectionMatrix(int width, int height);
	static void SetupModelViewMatrix(double phase);

	void DrawRectangle(float x1, float y1, float x2, float y2, float color) const;
	void DrawEmptyRectangle(float x1, float y1,
		float x2, float y2, float color) const;
	void DrawGradientRectangle(float x1, float y1, float x2,
		float y2, float color1, float color2) const;
	void DrawQuadrilateral(float x1, float y1, float x2, float y2,
		float x3, float y3, float x4, float y4, float color) const;
	void DrawCircle(float cx, float cy, float r, int num_segments, float color) const;
	void DrawHalfCircle(float cx, float cy, float r, float delta, int num_segments, float color) const;
	void DrawQuarterCircle(float cx, float cy, float r, float delta, int num_segments, float color) const;
	void DrawLine(float x1, float y1, float x2, float y2, float color) const;
	//void DrowEllipse(float centerCoordX, float centerCoordY, float rx, float ry, int pointCount, float color) const;

	void DrawBody(float centerCoordX, float centerCoordY) const;
	void DrawCrankShaft(float centerCoordX, float centerCoordY) const;
	void DrawConnectingRod(float centerCoordX, float centerCoordY) const;
	void DrawPiston(float x1, float y1, float x2, float y2, float color) const;
	void DrawCoolingFin(float x1, float y1, float x2, float y2, float color) const;
	void DrawCoolingFins(float centerCoordX, float centerCoordY, float color) const;
	void DrawValve(float coordX, float coordY, float color) const;
	void DrawUpPart(float coordX, float coordY) const;

	const std::chrono::milliseconds ANIMATION_PERIOD = std::chrono::milliseconds{ 8000 };
	//void DrawCircumference(float cx, float cy, float r, int num_segments, float color) const;
};