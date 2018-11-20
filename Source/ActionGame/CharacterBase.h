// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CharacterBase.generated.h"



class UAttributeSetBase;
class UGameplayAbilityBase;

UCLASS()
class ACTIONGAME_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		UAbilitySystemComponent* AbilitySystemComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		UAttributeSetBase* AttributeSetBaseComp;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;


	// AquireABility
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AquireAbilies(TArray<TSubclassOf<UGameplayAbility>> AbilityToAquire);

	///health
	UFUNCTION()
		void OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnHealthChanged"))
		void BP_OnHealthChanged(float Health, float MaxHealth);
	///Mana
	UFUNCTION()
		void OnManaChanged(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnManaChanged"))
		void BP_OnManaChanged(float Mana, float MaxMana);
	///Strength
	UFUNCTION()
		void OnStrengthChanged(float Strength, float MaxStrength);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnStrengthChanged"))
		void BP_OnStrengthChanged(float Strength, float MaxStrengtha);


	///death
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "Die"))
		void BP_Die();
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		bool isOtherHostile(ACharacterBase* Other);
	uint8 getTeamID()const;
	bool GetISDead()const;


	//Tag's
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AddGameplayTag(FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void RemoveGameplayTag(FGameplayTag& TagToRemove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		FGameplayTag FullHealthTag;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void HitStun(float StundDuration);

protected:
	bool isDead;
	uint8 TeamID;

	void AutoDeterminTeamIDbyControllerType();
	void Dead();

	void DisableInputControl();
	void EnableInputControl();

	FTimerHandle StunTimeHandle;

	void AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd);
};