#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsAnimationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICS_API UPhysicsAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsAnimationComponent();

	UFUNCTION(BlueprintCallable)
	void DeadStateReset();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Config)
	USkeletalMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	UCurveFloat* m_uCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float m_fBlendDuration = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FName m_OverrideAnimatedBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float m_fBlendWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	bool m_bDisable = false;

	float m_fTimer;
	FName m_AnimatedBone;
};
