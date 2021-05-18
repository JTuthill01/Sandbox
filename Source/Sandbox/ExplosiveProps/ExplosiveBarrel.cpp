#include "ExplosiveBarrel.h"

AExplosiveBarrel::AExplosiveBarrel()
{
	DamageRadius = 50.F;
}

void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void AExplosiveBarrel::OnPropHit_Implementation(int32 DamageToTake, FHitResult HitResult)
{
	Super::OnPropHit_Implementation(DamageToTake, HitResult);
}

void AExplosiveBarrel::SetDamage(int32 Damage, FHitResult HitResult, int32& DamageToApply)
{
	Super::SetDamage(Damage, HitResult, DamageToApply);
}

void AExplosiveBarrel::UpdateHealth(int32 Damage, bool& IsDead)
{
	Super::UpdateHealth(Damage, IsDead);
}
