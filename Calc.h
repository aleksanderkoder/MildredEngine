#pragma once

class Calc
{
	public:
		static double ToRadians(int deg); 
		static double* LineToLineCollision(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
		static double GetDistance(double x1, double y1, double x2, double y2);
		static double ToDegrees(double rad);
		static double NormalizeAngleRad(double angle);
		static double NormalizeAngleDeg(double angle);
};

