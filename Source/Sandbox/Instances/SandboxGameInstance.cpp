#include "SandboxGameInstance.h"

USandboxGameInstance::USandboxGameInstance() = default;

FAmmoData USandboxGameInstance::AK47Data()
{
	AK47AmmoData.Damage = 50.F;
	AK47AmmoData.CriticalHit = 10.F;
	AK47AmmoData.DamageRadius = 0.F;

	return AK47AmmoData;
}

FAmmoData USandboxGameInstance::AmericanShotgunData()
{
	AmericanShotgunAmmoData.Damage = 70.F;
	AmericanShotgunAmmoData.CriticalHit = 5.F;
	AmericanShotgunAmmoData.DamageRadius = 0.F;

	return AmericanShotgunAmmoData;
}

FAmmoData USandboxGameInstance::BelgianARData()
{
	BelgianARAmmoData.Damage = 65.F;
	BelgianARAmmoData.CriticalHit = 15.F;
	BelgianARAmmoData.DamageRadius = 0.F;

	return BelgianARAmmoData;
}

FAmmoData USandboxGameInstance::BulldogData()
{
	BulldogAmmoData.Damage = 85.F;
	BulldogAmmoData.CriticalHit = 5.F;
	BulldogAmmoData.DamageRadius = 0.F;

	return BulldogAmmoData;
}

FAmmoData USandboxGameInstance::HandCannonData()
{
	HandCannonAmmoData.Damage = 90.F;
	HandCannonAmmoData.CriticalHit = 5.F;
	HandCannonAmmoData.DamageRadius = 0.F;

	return HandCannonAmmoData;
}

FAmmoData USandboxGameInstance::L86Data()
{
	L86AmmoData.Damage = 60.F;
	L86AmmoData.CriticalHit = 8.F;
	L86AmmoData.DamageRadius = 0.F;

	return L86AmmoData;
}

FAmmoData USandboxGameInstance::ShortStrokeARData()
{
	ShortStrokeARAmmoData.Damage = 55.F;
	ShortStrokeARAmmoData.CriticalHit = 10.F;
	ShortStrokeARAmmoData.DamageRadius = 0.F;

	return ShortStrokeARAmmoData;
}

FAmmoData USandboxGameInstance::SKSData()
{
	SKSAmmoData.Damage = 80.F;
	SKSAmmoData.CriticalHit = 90.F;
	SKSAmmoData.DamageRadius = 0.F;

	return SKSAmmoData;
}

FAmmoData USandboxGameInstance::SMGData()
{
	SMGAmmoData.Damage = 52.F;
	SMGAmmoData.CriticalHit = 6.F;
	SMGAmmoData.DamageRadius = 0.F;

	return SMGAmmoData;
}

FAmmoData USandboxGameInstance::T38Data()
{
	T38AmmoData.Damage = 59.F;
	T38AmmoData.CriticalHit = 15.F;
	T38AmmoData.DamageRadius = 0.F;

	return T38AmmoData;
}

FAmmoData USandboxGameInstance::XM82Data()
{
	XM82AmmoData.Damage = 59.F;
	XM82AmmoData.CriticalHit = 10.F;
	XM82AmmoData.DamageRadius = 0.F;

	return XM82AmmoData;
}

