// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PhysicsAnimationComponent.h"
#include "PhysicsAnimationComponent.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include "AIController.h"

// Sets default values for this component's properties
UPhysicsAnimationComponent::UPhysicsAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPhysicsAnimationComponent::DeadStateReset()
{
	m_fTimer = 0.f;
	m_fBlendWeight = 1.f;
	m_Mesh->SetAllBodiesBelowSimulatePhysics(m_AnimatedBone, false, true);
	m_Mesh->SetAllBodiesBelowPhysicsBlendWeight(m_AnimatedBone, m_fBlendWeight);

}


// Called when the game starts
void UPhysicsAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* OwnerActor = GetOwner())
	{
		m_Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
		OwnerActor->OnTakePointDamage.AddDynamic(this, &UPhysicsAnimationComponent::OnTakePointDamage);
	}
	m_fTimer = 0.f;
}

void UPhysicsAnimationComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (!m_Mesh)
	{
		return;
	}

	if (m_bDisable)
	{
		return;
	}
	 
	//m_Mesh->SetAllBodiesBelowPhysicsBlendWeight
	m_fTimer = m_fBlendDuration;

	if(!m_OverrideAnimatedBone.IsNone())
	{
		m_AnimatedBone = m_OverrideAnimatedBone;
	}
	else
	{
		m_AnimatedBone = BoneName;
	}
 	m_Mesh->SetAllBodiesBelowSimulatePhysics(m_AnimatedBone, true, true);
}

// Called every frame
void UPhysicsAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(m_Mesh && !m_bDisable)
	{
		if (m_uCurve && m_fTimer > 0.f)
		{
			m_fTimer -= DeltaTime;
			m_fBlendWeight = m_uCurve->GetFloatValue(1 - (m_fTimer / m_fBlendDuration));
			m_Mesh->SetAllBodiesBelowPhysicsBlendWeight(m_AnimatedBone, m_fBlendWeight);
		}
		else
		{
			m_Mesh->SetAllBodiesBelowSimulatePhysics(m_AnimatedBone, false, true);
		}
	}
}

