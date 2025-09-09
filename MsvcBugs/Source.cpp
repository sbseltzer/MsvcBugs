#include <iostream>
#include <math.h>
#include <stdio.h>

void PrintOptimized()
{
	struct FVector { double X = sqrt(-1.0); double Y = sqrt(-1.0); double Z = sqrt(-1.0); } V;
	volatile double X = V.X;
	volatile double Y = V.Y;
	volatile double Z = V.Z;
	volatile double Tolerance = 0.000001;
	volatile double dX = abs(X - V.X);
	volatile double dY = abs(Y - V.Y);
	volatile double dZ = abs(Z - V.Z);
	// Comparison A
	{
		// This succeeds on Windows x86-64, fails on MacOS ARM64
		volatile bool bTolerates = (dX <= Tolerance) && (dY <= Tolerance) && (dZ <= Tolerance);
		bool bResult = bTolerates;
		printf("Result: %d %f %f %f %f\n", bResult, dX, dY, dZ, Tolerance);
	}
	// Comparison B
	{
		// This fails on Windows x86-64, fails on MacOS ARM64
		// Stranger yet, when optimization is turned off, it succeeds on Windows x86-64
		volatile bool bToleratesX = (dX <= Tolerance);
		volatile bool bToleratesY = (dY <= Tolerance);
		volatile bool bToleratesZ = (dZ <= Tolerance);
		bool bResult = bToleratesX && bToleratesY && bToleratesZ;
		printf("Result: %d %f %f %f %f %d %d %d\n", bResult, dX, dY, dZ, Tolerance, bToleratesX, bToleratesY, bToleratesZ);
	}
}

__pragma(optimize("", off))
void PrintUnoptimized()
{
	struct FVector { double X = sqrt(-1.0); double Y = sqrt(-1.0); double Z = sqrt(-1.0); } V;
	volatile double X = V.X;
	volatile double Y = V.Y;
	volatile double Z = V.Z;
	volatile double Tolerance = 0.000001;
	volatile double dX = abs(X - V.X);
	volatile double dY = abs(Y - V.Y);
	volatile double dZ = abs(Z - V.Z);
	// Comparison A
	{
		// This succeeds on Windows x86-64, fails on MacOS ARM64
		volatile bool bTolerates = (dX <= Tolerance) && (dY <= Tolerance) && (dZ <= Tolerance);
		bool bResult = bTolerates;
		printf("Result: %d %f %f %f %f\n", bResult, dX, dY, dZ, Tolerance);
	}
	// Comparison B
	{
		// This fails on Windows x86-64, fails on MacOS ARM64
		// Stranger yet, when optimization is turned off, it succeeds on Windows x86-64
		volatile bool bToleratesX = (dX <= Tolerance);
		volatile bool bToleratesY = (dY <= Tolerance);
		volatile bool bToleratesZ = (dZ <= Tolerance);
		bool bResult = bToleratesX && bToleratesY && bToleratesZ;
		printf("Result: %d %f %f %f %f %d %d %d\n", bResult, dX, dY, dZ, Tolerance, bToleratesX, bToleratesY, bToleratesZ);
	}
}
__pragma(optimize("", on))

int main(int argc, char** argv)
{
	PrintOptimized();
	PrintUnoptimized();
	return 0;
}