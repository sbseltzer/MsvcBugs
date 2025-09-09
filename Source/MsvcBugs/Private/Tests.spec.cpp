#include "Misc/AutomationTest.h"

// All of the following tests should succeed.

BEGIN_DEFINE_SPEC(FBugTestSpec, "Bugs.Optimized", EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)
END_DEFINE_SPEC(FBugTestSpec)

void FBugTestSpec::Define()
{
	Describe("NAN", [this]()
	{
		It("Non-compliant reproduction A", [this]()
		{
			FVector V = FVector{FMath::Sqrt(-1.0), FMath::Sqrt(-1.0), FMath::Sqrt(-1.0)};
			volatile double X = V.X;
			volatile double Y = V.Y;
			volatile double Z = V.Z;
			volatile double Tolerance = UE_KINDA_SMALL_NUMBER;
			volatile double dX = FMath::Abs(X-V.X);
			volatile double dY = FMath::Abs(Y-V.Y);
			volatile double dZ = FMath::Abs(Z-V.Z);
			// Comparison A
			{
				// This succeeds on Windows x86-64, fails on MacOS ARM64
				volatile bool bTolerates = (dX <= Tolerance) && (dY <= Tolerance) && (dZ <= Tolerance);
				bool bResult = TestFalse("InvalidVector != InvalidVector", bTolerates);
				UE_LOG(LogTemp, Warning, TEXT("Result: %d %f %f %f %f"), bResult, dX, dY, dZ, Tolerance);
			}
		});
		It("Non-compliant reproduction B", [this]()
		{
			FVector V = FVector{FMath::Sqrt(-1.0), FMath::Sqrt(-1.0), FMath::Sqrt(-1.0)};
			volatile double X = V.X;
			volatile double Y = V.Y;
			volatile double Z = V.Z;
			volatile double Tolerance = UE_KINDA_SMALL_NUMBER;
			volatile double dX = FMath::Abs(X-V.X);
			volatile double dY = FMath::Abs(Y-V.Y);
			volatile double dZ = FMath::Abs(Z-V.Z);
			// Comparison B
			{
				// This fails on Windows x86-64, fails on MacOS ARM64
				// Stranger yet, when optimization is turned off, it succeeds on Windows x86-64
				volatile bool bToleratesX = (dX <= Tolerance);
				volatile bool bToleratesY = (dY <= Tolerance);
				volatile bool bToleratesZ = (dZ <= Tolerance);
				bool bResult = TestFalse("InvalidVector != InvalidVector", bToleratesX && bToleratesY && bToleratesZ);
				UE_LOG(LogTemp, Warning, TEXT("Result: %d %f %f %f %f %d %d %d"), bResult, dX, dY, dZ, Tolerance, bToleratesX, bToleratesY, bToleratesZ);
			}
		});
	});
}

BEGIN_DEFINE_SPEC(FBugTestSpec_Unoptimized, "Bugs.Unoptimized", EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)
END_DEFINE_SPEC(FBugTestSpec_Unoptimized)

UE_DISABLE_OPTIMIZATION
void FBugTestSpec_Unoptimized::Define()
{
	Describe("NAN", [this]()
	{
		It("Non-compliant reproduction A", [this]()
		{
			FVector V = FVector{FMath::Sqrt(-1.0), FMath::Sqrt(-1.0), FMath::Sqrt(-1.0)};
			volatile double X = V.X;
			volatile double Y = V.Y;
			volatile double Z = V.Z;
			volatile double Tolerance = UE_KINDA_SMALL_NUMBER;
			volatile double dX = FMath::Abs(X-V.X);
			volatile double dY = FMath::Abs(Y-V.Y);
			volatile double dZ = FMath::Abs(Z-V.Z);
			// Comparison A
			{
				// This succeeds on Windows x86-64, fails on MacOS ARM64
				volatile bool bTolerates = (dX <= Tolerance) && (dY <= Tolerance) && (dZ <= Tolerance);
				bool bResult = TestFalse("InvalidVector != InvalidVector", bTolerates);
				UE_LOG(LogTemp, Warning, TEXT("Result: %d %f %f %f %f"), bResult, dX, dY, dZ, Tolerance);
			}
		});
		It("Non-compliant reproduction B", [this]()
		{
			FVector V = FVector{FMath::Sqrt(-1.0), FMath::Sqrt(-1.0), FMath::Sqrt(-1.0)};
			volatile double X = V.X;
			volatile double Y = V.Y;
			volatile double Z = V.Z;
			volatile double Tolerance = UE_KINDA_SMALL_NUMBER;
			volatile double dX = FMath::Abs(X-V.X);
			volatile double dY = FMath::Abs(Y-V.Y);
			volatile double dZ = FMath::Abs(Z-V.Z);
			// Comparison B
			{
				// This fails on Windows x86-64, fails on MacOS ARM64
				// Stranger yet, when optimization is turned off, it succeeds on Windows x86-64
				volatile bool bToleratesX = (dX <= Tolerance);
				volatile bool bToleratesY = (dY <= Tolerance);
				volatile bool bToleratesZ = (dZ <= Tolerance);
				bool bResult = TestFalse("InvalidVector != InvalidVector", bToleratesX && bToleratesY && bToleratesZ);
				UE_LOG(LogTemp, Warning, TEXT("Result: %d %f %f %f %f %d %d %d"), bResult, dX, dY, dZ, Tolerance, bToleratesX, bToleratesY, bToleratesZ);
			}
		});
	});
}
UE_ENABLE_OPTIMIZATION
