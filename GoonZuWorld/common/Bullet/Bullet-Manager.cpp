#include "..\Client\Client.h"

#include "..\Client\Music\Music.h"

#include "bullet.h"
#include "..\Smoke\Smoke.h"
#include "Util\Util.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;


// �Ѿ� �ӵ� ���� 
#define BLTSPEED(x) (x)

cltBulletManager::cltBulletManager(SI32 gamemode)
{
	SI32 i;

	InitBulletKindInfo();

	if(gamemode == GAMEMODE_SERVER)
	{
		for(i = 0;i < MAX_BULLET_NUMBER;i++)
		{
			BulletInfo[i] = 0;

			pclBullet[i] = new cltBulletServer();
		}
	}
	else
	{

		for(i = 0;i < MAX_BULLET_NUMBER;i++)
		{
			BulletInfo[i] = 0;

			pclBullet[i] = new cltBulletClient;
		}
	}
}


cltBulletManager::~cltBulletManager()
{
	SI32 i;

	for(i = 0;i < MAX_BULLET_NUMBER;i++)
	{
		if(pclBullet[i])
		{
			delete pclBullet[i];
			pclBullet[i] = NULL;
		}
	}

}

SI32 cltBulletManager::FindEmptyBullet()
{
	int i;

	for(i=1;i<MAX_BULLET_NUMBER;i++)
	{
		if(BulletInfo[i]==0)return i;
	}

	return 0;
}

void cltBulletManager::DeleteBullet(SI32 id)
{
	BulletInfo[id]	=	0;
}

void cltBulletManager::DeleteBullet()
{
	SI32 i;

	for(i = 0;i < MAX_BULLET_NUMBER;i++)
	{
		DeleteBullet(i);
	}
}


SI32 cltBulletManager::SetBullet(cltMapCommon* pclmap, SHORT kind, SHORT magickind,
								 SI32 shooter_id, 
								 SHORT apower,  
								 const cltPos* pcltilestartpos, 
								 const cltPos* pcldotstartpos, 
								 const cltAttackTarget* pcltarget, 
								 const cltPos* pcldotdestpos)
{
	SI32 id = FindEmptyBullet();
	if(id == 0)return 0;

	if(id >= MAX_BULLET_NUMBER)
	{
		MsgBox(TEXT("Smoke"), TEXT("adfsje65 : %d"), kind);
		return 0;
	}

	if(pclmap->IsInMapArea(pcltarget->clPos.siX, pcltarget->clPos.siY) == false)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("SetBullet()12 map:%d x:%d y:%d"),
			pclClient->pclCM->CR[shooter_id]->GetMapIndex(),pcltarget->clPos.siX, pcltarget->clPos.siY); 
		return 0;
	}

	if(pclmap->IsInMapArea(pcltilestartpos->siX, pcltilestartpos->siY) == true)
	{

		// �Ѿ� ��ü ���� ����. 
		if(pclBullet[id]->Init(pclmap, kind, magickind, id, 
			shooter_id, apower,  
			pcltilestartpos, 
			pcldotstartpos, 
			pcltarget, 
			pcldotdestpos, 
			&BKI[kind]) == true)
		{
			BulletInfo[id] = kind;
			return id;
		}
		// �Ѿ� ��ü ���� ����
		else
		{
			return 0;
		}
	}

	return 0;

}


BOOL cltBulletManager::Action()
{
	SI32 i;

	for(i = 0;i < MAX_BULLET_NUMBER;i++)
	{
		if(BulletInfo[i])
		{
			if(pclBullet[i]->Action() == FALSE)
			{
				DeleteBullet(i);
			}
		}
	}
	return TRUE;
}

BOOL cltBulletManager::Draw()
{
	SI32 i;

	for(i = 0;i < MAX_BULLET_NUMBER;i++)
	{
		if(BulletInfo[i])
		{
			pclBullet[i]->Draw();
		}
	}

	return TRUE;
}


void cltBulletManager::InitBulletKindInfo()
{
	cltBulletLayerInfo	clLayerInfo;
	cltBulletSoundInfo	clSoundInfo;
	cltBulletDrawInfo	clDrawInfo;

	cltBulletadjust		DefaultBulletAdjust;
	DefaultBulletAdjust.Init();	

	// ��	
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_GUN")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet.Spr"), NULL, DefaultBulletAdjust, 0, 1,  0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_GUN].Init(BLTSPEED(63), FALSE, FALSE, 
		ATTACKTYPE_GUN, 
		0,
		0, 2,
		//SMOKE_GUN, 0,				// �Ѿ� ���� �ذ԰� ��� ���޶�� �ؼ���...
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ȭ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Arrow.Spr"), NULL,DefaultBulletAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_ARROW].Init(BLTSPEED(60),FALSE, FALSE, 
		ATTACKTYPE_BOW, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ȣ���Ҹ� �� ������
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_CAKE")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CAKE")) );
	clDrawInfo.Set( TEXT("Bullet\\Cake.Spr"), NULL, DefaultBulletAdjust, 0, 3, 0, false, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_CAKE].Init(BLTSPEED(35), FALSE, FALSE, 
		ATTACKTYPE_CAKE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ޱ��� �� ������
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CHICKEN_ATTACK")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Egg.Spr"), NULL, DefaultBulletAdjust, 0, 4, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_EGG].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_EGG, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ȸ�� ������ ��ź

	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")) );
	clDrawInfo.Set( TEXT("Bullet\\CannonBall.Spr"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_FIRESMOKE, false, TRANSPARENT_MODE_NORMAL, 0);
	//clDrawInfo.Set( TEXT("Bullet\\CannonBall.Spr"), 0, 8, 0, false, 0 );
	BKI[BULLETKIND_CANNONBALL].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_CANNON,
		0,
		0, 2,
		0, SMOKE_CANNONEXP,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ź��� ��� ������
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_TURTLE_ATTACK")), 
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\TurtleBackShell.Spr"), NULL, DefaultBulletAdjust, 0, 3, 0, false, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_TURTLEBACKSHELL].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_SHELL, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ȭ���ӱ� 
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MagicFireBall.Spr"), TEXT("Bullet\\MagicFireBallLight.spr"), DefaultBulletAdjust, 0, 8, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_MAGICFIREBALL].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, SMOKE_FIREBALLHIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ź� ��ǳ
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_BIGWIND_FIRE")) ,
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\MagicBigWind.Spr"), TEXT("Bullet\\MagicBigWindLight.Spr"), DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN) ;
	BKI[BULLETKIND_MAGICBIGWIND].Init(BLTSPEED(25), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ȸ����

	clLayerInfo.Init();
	//clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_BIGWIND_FIRE")) ,
	//	pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Harpy_bullet.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, false, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_HARPY].Init(BLTSPEED(25), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ޱ� ��ǳ
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CATFISH_ATTACK")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\CatFishBigWind.Spr"), NULL, DefaultBulletAdjust,  0, 8, false, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_CATFISH].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������ ��ä
	clLayerInfo.Init();
	clSoundInfo.Set( 0, 0);
	clDrawInfo.Set( TEXT("Bullet\\LadyBugFan.Spr"), NULL, DefaultBulletAdjust, 0, 5, false, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_LADYBUGFAN].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_LADYBUGFAN, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���ǿ��� �� ������
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_CAKE")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CAKE")) );
	clDrawInfo.Set( TEXT("Bullet\\Snow.Spr"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_SNOW].Init( BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_SNOW, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������ ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_STAFF_FIRE")), 0);
	clDrawInfo.Set( TEXT("Bullet\\MagicStaff1.Spr"), TEXT("Bullet\\MagicStaff1Light.spr"), DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN) ;
	BKI[BULLETKIND_STAFF1].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_STAFF1, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������ ��
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MadoGhostFire.Spr"), NULL, DefaultBulletAdjust, 0, 8, 0, false, TRANSPARENT_MODE_NORMAL, 0) ;	
	BKI[BULLETKIND_MADOGHOSTFIRE].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_MADOGHOSTFIRE,
		0,
		0, 2,
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ּ��ֱ� �����°�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_JapanHealer.Spr"),NULL, DefaultBulletAdjust, 0, 4, 0, false, TRANSPARENT_MODE_NORMAL, 0);	
	BKI[BULLETKIND_JAPANHEADER].Init          (BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_JAPANHEADER,
		0,
		0, 2,
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� �䱫 �̻���
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Tohang.Spr"), NULL, DefaultBulletAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_TOHANG].Init        (BLTSPEED(35), FALSE, FALSE, 
		ATTACKTYPE_TOHANG, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	// �ذ� ���� ������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_SkullBatFire.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SKULLBATFIRE].Init(BLTSPEED(15), FALSE, FALSE, 
		ATTACKTYPE_SKULLBATFIRE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ����� 
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_FIREGOBLIN.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_FIREGOBLIN].Init(BLTSPEED(15), FALSE, FALSE, 
		ATTACKTYPE_FIREGOBLIN, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ��ź. 
	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")));
	clDrawInfo.Set( TEXT("Bullet\\CastleBall.Spr"), NULL, DefaultBulletAdjust, 0, 5, SMOKE_FIRESMOKE, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_CASTLECANNONBALL].Init(BLTSPEED(10), FALSE, FALSE, 
		ATTACKTYPE_CASTLECANNON,
		BLTATB_CURVE|BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_CASTLEBOOM,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ��ź. 
	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")));
	clDrawInfo.Set( TEXT("Bullet\\CastleBall.Spr"), NULL, DefaultBulletAdjust, 0, 5, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SELFBOMB].Init(BLTSPEED(10), FALSE, FALSE, 
		ATTACKTYPE_CASTLECANNON,
		BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_SELFDESTUCT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	// ��	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\PoisonBullet.Spr"), NULL, DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_MAGICPOISON].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_POISON, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);	

	// ICE
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\IceBullet.Spr"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_ICESMOKE, true, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_MAGICICE].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_ICE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// KNIFE
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Knife.Spr"), NULL, DefaultBulletAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_KNIFE].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_KNIFE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��� FireBall
	clLayerInfo.Init();
	clSoundInfo.Init();	// �Ѿ��� 9���� 
	clDrawInfo.Set( TEXT("Bullet\\GreenFire.Spr"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_GREENFIRE].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_GREENFIRE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����ָ�  
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicLightingFist.Spr"), NULL, DefaultBulletAdjust,  0, 7, 0, false, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_MAGICLIGHTINGFIST].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Թ� 
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\BlackInk.SPR"), NULL, DefaultBulletAdjust,  0, 1, 0, false, TRANSPARENT_MODE_MULTIPLY, 0);
	BKI[BULLETKIND_BLACKINK].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_BLACKINK, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �θ޶� ---- ���� �׸��� ����.
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\StoneBoomerang.spr"), NULL, DefaultBulletAdjust, 0, 4, 0, true, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_BOOMERANG].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_BOOMERANG,
		BLTATB_BOOMERANG|BLTATB_RANGE2,
		0, 2,
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���Ż �ٶ�Į��
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_WindBlade.SPR"), NULL, DefaultBulletAdjust, 0, 5, SMOKE_WINDBLADE, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_WINDBLADE].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_WINDBLADE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������� ��ź
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_ShellFishBomb.SPR"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_FIRESMOKE, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SHELLFISHBOMB].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_SHELLFISHBOMB, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_TREEMON].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_TREEMON, 
		0,
		0, 2,
		0, SMOKE_TREEMON, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ܴ�����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_VINE].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_VINE, 
		0,
		0, 2,
		0, SMOKE_VINE, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���ɱͽ�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_GHOSTFIRE, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_GHOSTFIRE].Init(BLTSPEED(35), FALSE, FALSE, 
		ATTACKTYPE_GHOSTFIRE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SIMTORYONG].Init(BLTSPEED(70), FALSE, FALSE, 
		ATTACKTYPE_SIMTORYONG, 
		0,
		0, 2,
		0, SMOKE_SIMTORYONGSTONE, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��տ�����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_CuttleFish.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_KINGCUTTLEFISH].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_KINGCUTTLEFISH, 
		0,
		0, 2,
		0, SMOKE_KINGCUTTLEFISH, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ź������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Crane.Spr"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_CRANE_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_CRANE].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_CRANE,
		BLTATB_CURVE|BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_CRANE_HIT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���� ����
	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")));
	clDrawInfo.Set( TEXT("Bullet\\CastleBall.Spr"), NULL, DefaultBulletAdjust, 0, 5, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SELFBOMBWHALE].Init(BLTSPEED(10), FALSE, FALSE, 
		ATTACKTYPE_CASTLECANNON,
		BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_SELFBOMBWHALE,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	//  ź��������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\bullet_monkeydrill.Spr"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_MONKEYDRILL].Init( BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_MONKEY, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	//  ���� ���� ���� 
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicSpitCurse.Spr"), NULL, DefaultBulletAdjust,  0, 1, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_ADD, 0);
	BKI[BULLETKIND_MAGICCURSEDEFENSE].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_CURSEDEFENSE, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �̵��ӵ� ���� ���� 
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicSpitCurse.Spr"), NULL, DefaultBulletAdjust,  0, 1, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_ADD, 0);
	BKI[BULLETKIND_MAGICCURSEMOVESPEED].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_CURSEMOVESPEED, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���ּ�����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Butcher.SPR"), NULL, DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_NORMAL,0);
	BKI[BULLETKIND_BUTCHER].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_BUTCHER, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���ϸ���
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_StoneOldMan.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_NORMAL,0);
	BKI[BULLETKIND_STONEOLDMAN].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_STONEOLDMAN, 
		0,
		0, 2,
		0, SMOKE_CRANE_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	// ������ ������ 
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicThrowKnifeRight.SPR"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_THROWKNIFE_RIGHT, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_MAGICTHROWKNIFE_RIGHT].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ������ ����  
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicThrowKnifeLeft.SPR"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_THROWKNIFE_LEFT, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_MAGICTHROWKNIFE_LEFT].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��ռҶ��
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_KingCrab.SPR"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_KINGCRAB_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_KINGCRAB].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_KINGCRAB, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��ȭ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_FireArrow.SPR"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_FIREARROW].Init(BLTSPEED(60), FALSE, FALSE, 
		ATTACKTYPE_FIREARROW, 
		0,
		0, 2,
		0, SMOKE_FIREBALLHIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Lobster.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_LOBSTER].Init(BLTSPEED(60), FALSE, FALSE, 
		ATTACKTYPE_LOBSTER, 
		0,
		0, 2,
		0, SMOKE_FIREBALLHIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���»���  
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_DeadMessenger.SPR"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_DEADMESSENGER, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_DEADMESSENGER].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_DEADMESSENGER, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ��Ż
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_MASKMONK].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_MASKMONK, 
		0,
		0, 2,
		0, SMOK_MASKMONK_STONE, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo,
		SMOK_MASKMONK_DROPSTONE
		);
	// �ֹ��� ���� ����
	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")) );
	clDrawInfo.Set( TEXT("Bullet\\CastleBall.Spr"), NULL, DefaultBulletAdjust, 0, 5, SMOKE_FIRESMOKE, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_PERSONCANNON].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_PERSONCANNON,
		BLTATB_CURVE|BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_PERSONCANNON_HIT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ֹ��� ���� ����
	clLayerInfo.Init();
	clSoundInfo.Set( 0, pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_CANNON")) );
	clDrawInfo.Set( TEXT("Bullet\\CastleBall.Spr"), NULL, DefaultBulletAdjust, 0, 5, SMOKE_FIRESMOKE, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_CANNON_MAGIC].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_CANNON_MAGIC,
		BLTATB_CURVE|BLTATB_RANGE3,
		0, 2,
		0, 	SMOKE_MAGICFREEZEEXPLOSION,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ѽ� ����(1��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_GUN")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_GunScroll.SPR"), NULL, DefaultBulletAdjust,  0, 1, SMOKE_GUNSCROLL_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_GUN_SCROLL].Init(BLTSPEED(63), FALSE, FALSE, 
		ATTACKTYPE_GUN1, 
		0,
		0, 2,
		//SMOKE_GUN, 0,				// �Ѿ� ���� �ذ԰� ��� ���޶�� �ؼ���...
		0, SMOKE_GUNSCROLL_HIT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ѽ� ����(2��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_GUN")), 
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_GUN")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_New_GunScroll.SPR"), NULL, DefaultBulletAdjust,  0, 1, SMOKE_NEW_GUNSCROLL_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_NEW_GUN_SCROLL].Init(BLTSPEED(63), FALSE, FALSE, 
		ATTACKTYPE_NEW_GUN1, 
		0,
		0, 2,
		//SMOKE_GUN, 0,				// �Ѿ� ���� �ذ԰� ��� ���޶�� �ؼ���...
		0, SMOKE_NEW_GUNSCROLL_HIT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ü� ����(1��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BowScroll.Spr"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_BOWSCROLL_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_BOW_SCROLL].Init(BLTSPEED(60),FALSE, FALSE,
		ATTACKTYPE_BOW1, 
		0,
		0, 2,
		0, SMOKE_BOWSCROLL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ü� ����(2��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_New_BowScroll.Spr"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_NEW_BOWSCROLL_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_NEW_BOW_SCROLL].Init(BLTSPEED(60),FALSE, FALSE,
		ATTACKTYPE_NEW_BOW1, 
		0,
		0, 2,
		0, SMOKE_NEW_BOWSCROLL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����̼� ����(1��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_STAFF_FIRE")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_StaffScroll.spr"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_STAFFSCROLL_TAIL, true, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_STAFF_SCROLL].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_STAFF2, 
		0,
		0, 2,
		0, SMOKE_STAFFSCROLL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����̼� ����(2��) �߶��� ��
	clLayerInfo.Init();
	clSoundInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_STAFF_FIRE")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_StaffScroll.spr"), NULL, DefaultBulletAdjust, 0, 8, SMOKE_NEW_STAFFSCROLL_TAIL, true, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_NEW_STAFF_SCROLL].Init( BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_NEW_STAFF2, 
		0,
		0, 2,
		0, SMOKE_NEW_STAFFSCROLL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ա���
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\BULLETKIND_FOAM_FIRE.SPR"), NULL, DefaultBulletAdjust, 0, 5, 0, true, TRANSPARENT_MODE_NORMAL,0);
	BKI[BULLETKIND_FOAM_FIRE].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_FOAM,
		0,
		0, 2,
		0, SMOKE_FOAM_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// �Ϲݰ������� ȭ���ӱ���
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MagicFireBall.Spr"), TEXT("Bullet\\MagicFireBallLight.spr"), DefaultBulletAdjust, 0, 8, SMOKE_FIRESMOKE, true, TRANSPARENT_MODE_NORMAL, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_FIREBALL].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_FIREBALL, 
		0,
		0, 2,
		0, SMOKE_FIREBALLHIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// �Ϲݰ������� ȭ���ӱ���
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_MORTAL].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MORTAL, 
		BLTATB_RANGE1,
		0, 2,
		SMOKE_MORTAL_FIRE, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ��ȭ��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_ARROW")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_ARROW")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_WaterArrow.SPR"), NULL, DefaultBulletAdjust, 0, 1, SMOKE_WATERARROW_TAIL, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_WATERARROW].Init(BLTSPEED(60), FALSE, FALSE, 
		ATTACKTYPE_WATERARROW, 
		0,
		0, 2,
		0, SMOKE_WATERARROW_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	//[����] Ÿ�� �극��ũ ����� ��밡 ������ ���� ����. => 2008-5-9
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_PalmWind.Spr"), NULL, DefaultBulletAdjust, 0, 9, SMOKE_PALMWIND_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULETKIND_MAGICPALMWIND].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_CURSEMOVESPEED, 
		0,
		0, 2,
		0, SMOKE_MAGIC_PALMWIND_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ����� ��ǳ
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_PalmWind.Spr"), NULL, DefaultBulletAdjust, 0, 9, SMOKE_PALMWIND_TAIL, true, TRANSPARENT_MODE_SCREEN, 0) ;
	BKI[BULLETKIND_STAFFWIND].Init(BLTSPEED(25), FALSE, FALSE,
		ATTACKTYPE_STAFFWIND, 
		0,
		0, 2,
		0, SMOKE_FIREBALLHIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���ư��� ����(����?)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_FlyVine.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_FLYVINE].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_FLYVINE, 
		0,
		0, 2,
		0, SMOKE_DOWNING_VINE, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �ذ����� ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Magic_SkellGhost.SPR"), NULL, DefaultBulletAdjust, 0, 4, SMOKE_MAGIC_SKELLGHOST_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_MAGICSKELLGHOST].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		SMOKE_MAGIC_SKELLGHOST_FIRE, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���ư��� ������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_SkellFish.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_SKELLFISH].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_SKELLFISH, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// MagicFrozen
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicFrozen.Spr"), NULL, DefaultBulletAdjust, 0, 6, SMOKE_MAIGCFROZEN_TAIL, true, TRANSPARENT_MODE_NORMAL, 0) ;
	BKI[BULLETKIND_MAGICFROZEN].Init( BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_FROZEN, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��������
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_FROZEN_FIRE")),0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Trans.SPR"), NULL, DefaultBulletAdjust, 0, 1, 0, false, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_ICESTONE].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_ICESTONE, 
		0,
		0, 2,
		0, SMOKE_ICESTONE_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �糯â
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\TwinSpear.Spr"), NULL, DefaultBulletAdjust, 0, 10, SMOKE_TWINSPEAR_TAIL, false, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_TWINSPEAR].Init(BLTSPEED(40), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��ǳ
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAGIC_NORTHWIND_FIRE")),0);
	clDrawInfo.Set( TEXT("Bullet\\NorthWind.Spr"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_NORTHWIND].Init(BLTSPEED(40), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, SMOKE_NORTHWIND_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ȭ����ǳ
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\FireStorm.Spr"),NULL,DefaultBulletAdjust, 0, 9,SMOKE_FIRESTORM_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_FIRESTORM].Init(BLTSPEED(40), FALSE, FALSE,
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���ȱ�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\EnergyArrow.SPR"), NULL, DefaultBulletAdjust, 0, 7, 0, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_ENERGYARROW].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_ENERGYARROW, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� �Ϲ� ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Spear_Mana.SPR"), NULL, DefaultBulletAdjust, 0, 7, SMOKE_SPEAR_MANA_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_SPEAR_MANA].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_SPEAR_MANA, 
		0,
		0, 2,
		0, SMOKE_SPEAR_DRAGON_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ���� ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Spear_Dragon.SPR"), NULL, DefaultBulletAdjust, 0, 9, SMOKE_SPEAR_DRAGON_TAIL, true, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_SPEAR_DRAGON].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 2,
		0, SMOKE_SPEAR_DRAGON_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ���� �θ�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BlackBoss.SPR"), NULL, DefaultBulletAdjust, 0, 16, 0, false, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_BLACKBOSS].Init(BLTSPEED(15), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Octopus.SPR"), NULL, DefaultBulletAdjust,  0, 5, 0, true, TRANSPARENT_MODE_NORMAL, 0);
	BKI[BULLETKIND_OCTOPUS].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_OCTOPUS, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ����������
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Otohime.SPR"), NULL, DefaultBulletAdjust, 0, 20, 0, false, TRANSPARENT_MODE_SCREEN, 0);
	BKI[BULLETKIND_OTOHIME].Init(BLTSPEED(10), FALSE, FALSE, 
		ATTACKTYPE_OTOHIME, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	cltBulletadjust clBlackSpider(0, 20, -15, 15, -30, 0, -15, -20, 0, -15);

	// ��Ź�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BlackSpider.spr"), NULL, clBlackSpider,  0, 11, 0, true, TRANSPARENT_MODE_SCREEN, 0, 25 );
	BKI[BULLETKIND_BLACKSPIDER].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_BLACKSPIDER, 
		0,
		0, 1,
		0, SMOKE_BLACKSPIDER_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �̺����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_EvilEye.spr"), NULL, DefaultBulletAdjust,  0, 12, 0, false , TRANSPARENT_MODE_SCREEN, 0 );
	BKI[BULLETKIND_EVILEYE].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_EVILEYE, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������ ����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicGargoyle.SPR"), NULL, DefaultBulletAdjust,  0, 10, 0, false , TRANSPARENT_MODE_SCREEN, 0, 30);
	BKI[BULLETKIND_GARGOYLE].Init(BLTSPEED(10), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	// �̺��ν� ����
	cltBulletadjust cerberusAdjust(0, 70, -90, 50, -125, -15, -90, -70, 0, -80);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicCerberus.spr"), NULL, cerberusAdjust,  0, 11, 0, true , TRANSPARENT_MODE_SCREEN, 0, 50);
	BKI[BULLETKIND_CERBERUS].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ������ �Ҽ���
	cltBulletadjust frozensorcererAdjust(0, 90, -67, 61, -90, 0, -57, -57, 0, -90);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\FrozenSorcerer_Bullet.SPR"), NULL, frozensorcererAdjust,  0, 4, 0, true , TRANSPARENT_MODE_SCREEN, 0, 50);
	BKI[BULLETKIND_FROZENSORCERER].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_FROZENSORCERER, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ��������Ʈ
	cltBulletadjust marionetteAdjust(0, 20, -15, 10, -20, 0, -15, -15, 0, -20);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicMarionette.spr"), NULL, DefaultBulletAdjust,  0, 6, 0, true , TRANSPARENT_MODE_SCREEN, 0, 50, 3);
	BKI[BULLETKIND_MARIONETTE].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ������
	cltBulletadjust frokenAdjust(0,50,	-40,30,	-50,-5,	-40,-30,	0,-50);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicFroken.SPR"), NULL, frokenAdjust,  0, 5, 0, true , TRANSPARENT_MODE_SCREEN, 0, 30, 3);
	BKI[BULLETKIND_FROKEN].Init(BLTSPEED(15), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ���̽��Ͽ��
	clLayerInfo.Init();
	clLayerInfo.Set(54, true);
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicIcehound.SPR"), NULL, DefaultBulletAdjust,  0, 6, 0, true , TRANSPARENT_MODE_SCREEN, 0, 50);
	BKI[BULLETKIND_ICEHOUND].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ��������Ʈ
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicFrozenKnight.SPR"), NULL, DefaultBulletAdjust,  0, 4, 0, true , TRANSPARENT_MODE_SCREEN, 0, 50);
	BKI[BULLETKIND_FROZENKNIGHT].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// �����Ǵ�
	clLayerInfo.Init();
	clLayerInfo.Set(36, true);
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicNinjapanda.SPR"), NULL, DefaultBulletAdjust,  0, 4, 0, true , TRANSPARENT_MODE_NORMAL, 0, 50);
	BKI[BULLETKIND_NINJAPANDA].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// �а��ʱ���
	clLayerInfo.Init();
	clLayerInfo.Set(63, true);
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicRaccoonDog.SPR"), NULL, DefaultBulletAdjust,  0, 7, 0, true , TRANSPARENT_MODE_NORMAL, 0, 50);
	BKI[BULLETKIND_RACCOONDOG].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ����������
	cltBulletadjust bossmonkeyAdjust(18, 54,	-66,68,	-120, 38,	-100,-20,	-25,-50);
	clLayerInfo.Init();
	clLayerInfo.Set(45, true);
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicBossMonkey.SPR"), NULL, bossmonkeyAdjust,  0, 5, 0, true , TRANSPARENT_MODE_NORMAL, 0, 50);
	BKI[BULLETKIND_BOSSMONKEY].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// ĳ�� ��( ����䱫)
	cltBulletadjust cannonmolAdjust(1, 87, -90, 68, -123, 9, -89, -27, 2, -52 );
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_CannonMol.Spr"), NULL, cannonmolAdjust, 0, 5, 0, FALSE, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_CANNONMOL].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_CANNONMOL, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��������
	cltBulletadjust bloodbatAdjust(-4, 119, -87, 91, -118, 7, -78, -61, 0, -103);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BLOODBAT_MAGIC")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BLOODBAT_MAGIC_HIT")));
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BloodBat.Spr"), NULL, bloodbatAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_BLOODBAT].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	// �����ΰ�
	cltBulletadjust werewolfAdjust(-25, 210, -185, 150, -240, 20, -160, -110, 15, -150);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WEREWOLF_MAGIC")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Werewolf.Spr"), NULL, werewolfAdjust, 0, 5, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_WEREWOLF].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	//Ÿ��������
	cltBulletadjust priestAdjust(-12, 111, -155, 76, -203, -3, -135, -81, 14, -108);
	clLayerInfo.Init();
	clLayerInfo.Set(18, true);
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_PRIEST_ATTACK")), 0);
	clDrawInfo.Init();
	BKI[BULLETKIND_PRIEST].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_PRIEST, 
		0,
		0, 1,
		0, SMOKE_GUNSCROLL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	//�ʿ��ź�
	cltBulletadjust GreenTurtleAdjust(-12, 111, -155, 76, -203, -3, -135, -81, 14, -108);
	clLayerInfo.Init();
	clDrawInfo.Init();
	clSoundInfo.Init();
	BKI[BULLETKIND_GREENTURTLE].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_GREENTURTLE, 
		0,
		0, 1,
		0, SMOKE_DRAGONEXPLOSION, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	//��������
	cltBulletadjust devilousAdjust(22, 0, -26, 4, -64, -15, -63, -45, -29, -62);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_DEVILOUS_MAGIC")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Devilous.Spr"), NULL, devilousAdjust, 0, 12, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_DEVILOUS].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	//����
	cltBulletadjust gangsiAdjust(-10, 120, -95, 95, -140, 5, -125, -85, -20, -130);
	clLayerInfo.Init();
	clLayerInfo.Set(9, true);
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_GANGSI_MAGIC")), 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Gangsi.Spr"), NULL, gangsiAdjust, 0, 1, 0, true, TRANSPARENT_MODE_NORMAL, 0, 0 );
	BKI[BULLETKIND_GANGSI].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	//�⸰
	cltBulletadjust GiraffeAdjust(-12, 111, -155, 76, -203, -3, -135, -81, 14, -108);
	clLayerInfo.Init();
	//clLayerInfo.Set();
	clSoundInfo.Set(0, 0);
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Giraffe.Spr"), NULL, GiraffeAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_GIRAFFE].Init(BLTSPEED(25), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, SMOKE_GIRAFFE_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	
	// ź���ҳ�
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_DYNAMITE_FIRE")), 
					pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_BOOM_HIT2")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_MineGirl.spr"), TEXT("Bullet\\Bullet_MineGirlLight.spr"), DefaultBulletAdjust,  0, 6, 0, true , TRANSPARENT_MODE_NORMAL, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_MINEGIRL].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MINEGIRL, 
		0,
		0, 1,
		0, SMOKE_MINEGIRL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����ø���	
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_MagicalRaccoon.SPR"), NULL, DefaultBulletAdjust,  0, 10, 0, true , TRANSPARENT_MODE_SCREEN, 0, 0);
	BKI[BULLETKIND_MAGICALRACCOON].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGICALRACCOON, 
		0,
		0, 1,
		0, SMOKE_MINEGIRL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��������	
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_MamaRaccoon.SPR"), NULL, DefaultBulletAdjust,  0, 12, 0, true , TRANSPARENT_MODE_SCREEN, 0, 0);
	BKI[BULLETKIND_MAMARACCOON].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGICALRACCOON, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ����Ÿ��	
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_RaccoonTower.SPR"), NULL, DefaultBulletAdjust,  0, 9, 0, true , TRANSPARENT_MODE_SCREEN, 0, 0);
	BKI[BULLETKIND_RACCOONTOWER].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_RACCOONTOWER, 
		0,
		0, 1,
		0, SMOKE_MINEGIRL_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �մޱ�	
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_ChickenBig.SPR"), NULL, DefaultBulletAdjust,  0, 8, 0, true , TRANSPARENT_MODE_SCREEN, 0, 0);
	BKI[BULLETKIND_CHICKENBIG].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_CHICKENBIG, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �򰭰��� - ���� (PCK - 07.12.27)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_MoonBlade.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_NORMAL, 0, 4);
	BKI[BULLETKIND_MOONBLADE].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_MOONBLADE, 
		0,
		0, 2,
		0, SMOKE_SPEAR_DRAGON_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �밻�� (PCK : 07.12.31)
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EMPERORARCHER_ATTACK")),
					 pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_EMPERORARCHER_HIT")) );	
	clDrawInfo.Set( TEXT("Bullet\\Bullet_EmperorArcherBowN.SPR"), NULL, DefaultBulletAdjust, 0, 9, 0, true, TRANSPARENT_MODE_SCREEN, 0, 4);
	BKI[BULLETKIND_EMPERORARCHER].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_EMPERORARCHER,
		0,
		0, 1,
		0, SMOKE_SPEAR_DRAGON_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ������(��) - ������ (PCK - 07.12.27)
	cltBulletadjust  NinjaAdjust(0, 35,/**/-30, 30,/**/-30, 0,/**/-30, -30,/**/ 0, -35);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_NinjaMan.SPR"), NULL, NinjaAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 50);
	BKI[BULLETKIND_NINJAMAN].Init(BLTSPEED(75), FALSE, FALSE, 
		ATTACKTYPE_NINJAMAN, 
		0,
		0, 1,
		0, SMOKE_SPEAR_DRAGON_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	
	// �������ذ�ú� [ȭ��]
	cltBulletadjust clPirateArcherAdjust( 0, 95,/**/-55, 35,/**/-75, 0,/**/-50, -40,/**/0, 75 );
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_PirateArcher.SPR"), NULL, clPirateArcherAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_PIRATEARCHER].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_PIRATEARCHER,
		0,
		0, 1,
		0, SMOKE_GUNSCROLL_HIT,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������ذ�ú� (PCK : 08.03.07) [����]
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicPirateArcher.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_SCREEN, 0, 0);
	BKI[BULLETKIND_PIRATEARCHER_MAGIC].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_MAGIC,
		0,
		0, 1,
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������ذ񺴻� (PCK : 08.03.08)
	//cltBulletadjust  clPirateSoldierAdjust( 0, 115,/**/-95, 95,/**/-115, 0,/**/-95, -95,/**/0, -115 );
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\MagicPirateSoldier.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_NORMAL);
	BKI[BULLETKIND_PIRATESOLDIER].Init(BLTSPEED(40), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �밻���� (PCK : 08.03.22)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_EmperorCavalry.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_EMPERORCAVALRY].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �밻�� (PCK : 08.03.22)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_EmperorMaster.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_EMPERORMASTER].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_EMPERORMASTER, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ӹ��� - �Ӹ������� (PCK : 08.04.07)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_GreatWallMagician.SPR"), NULL, DefaultBulletAdjust, 0, 7, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_GREATWALLMAGICIAN].Init(BLTSPEED(30), FALSE, FALSE, 
		ATTACKTYPE_GREATWALLMAGICIAN, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	
	// ����� ���Ǹ� ���Ÿ�
	clLayerInfo.Init();
	clSoundInfo.Set( 0,	pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_CATRANGE")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_CatRange.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_NORMAL);
	BKI[BULLETKIND_CATRANGE].Init(BLTSPEED(40), FALSE, FALSE, 
		ATTACKTYPE_CATRANGE, 
		0,
		0, 1,
		0, SMOKE_CATRANGE_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ��빫���񷽺��� (PCK : 08.05.28)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_EmperorWarrior.SPR"), TEXT("Bullet\\Bullet_EmperorWarriorFX.SPR"), DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_NORMAL, TRANSPARENT_MODE_SCREEN, 0 );
	BKI[BULLETKIND_EMPERORWARRIOR].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����强���� (PCK : 08.05.28)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_GreatWallSpider.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_GREATWALLSPIDER].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_GREATWALLSPIDER,
		0,
		0, 1,
		0, 0,
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����强�θӸ� (PCK : 08.05.28)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_GreatWallTwinHead.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_GREATWALLTWINHEAD].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� - �������� (PCK : 08.07.14)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BearTang.SPR"), NULL, DefaultBulletAdjust, 0, 4, 0, true, TRANSPARENT_MODE_NORMAL, 0, 0 );
	BKI[BULLETKIND_BEARTANG].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_BEARTANG, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� - �������� (PCK : 08.07.14)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BearTangMagic.SPR"), NULL, DefaultBulletAdjust, 0, 7, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_BEARTANG_MAGIC].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_POISON, 
		0,
		0, 50,
		0, SMOKE_BEARTANG_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������� - �������� (PCK : 08.07.14)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_SuperBearTang.SPR"), NULL, DefaultBulletAdjust, 0, 4, 0, FALSE, TRANSPARENT_MODE_NORMAL, 0, 0 );
	BKI[BULLETKIND_SUPERBEARTANG].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_SUPERBEARTANG, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������� - �������� (PCK : 08.07.14)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_BearTangMagic.SPR"), NULL, DefaultBulletAdjust, 0, 7, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_SUPERBEARTANG_MAGIC].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_POISON, 
		0,
		0, 50,
		0, SMOKE_SUPERBEARTANG_HIT, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	//[����] �ҷ���
	//cltBulletadjust  HalloweenGhostAdjust(0, 35,/**/-30, 30,/**/-30, 0,/**/-30, -30,/**/ 0, -35);
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_HalloweenGhost.SPR"), NULL, DefaultBulletAdjust, 0, 11, 0, false, TRANSPARENT_MODE_SCREEN, 0, 50 );
	BKI[BULLETKIND_HALLOWEENGHOST].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_HALLOWEENGHOST, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// Ʈ���õ���(Ȱ ����)
	cltBulletadjust  clTripleDeathAdjust( 0, 65,/**/-55, 50,/**/-65, 0,/**/-55, -50,/**/ 0, -55 );
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\bullet_tripledeath.spr"), NULL, clTripleDeathAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, -200 );
	BKI[BULLETKIND_TRIPLEDEATH_MAGIC].Init(BLTSPEED(50), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �����䳢 (PCK : 08.10.15)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_Cosmosrabbit.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, false, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_COSMOSRABBIT].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);	

	//ũ�������� ���Ÿ�����
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_CHRISTMASRANGE.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_CHRISTMASRANGE].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_CHRISTMASRANGE, 
		0,
		0, 0,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);	

	// ��ȯ�� �絹�� - ���� ��ź (PCK : 08.11.19)
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_RUDOLPHPET_MAGIC")), 0 );
	clDrawInfo.Set( TEXT("Bullet\\MagicRUDOLPH.spr"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_RUDOLPHPET].Init(BLTSPEED(20), FALSE, FALSE, 
		ATTACKTYPE_MAGIC, 
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ����������Ƽ��� - �Ҳ� ���. (OJY : 09.02.10)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_GreatWallAsura.spr"), NULL, DefaultBulletAdjust, 0, 4, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_GREATWALLASURA].Init(BLTSPEED(20), FALSE, FALSE,
		ATTACKTYPE_GREATWALLASURA,
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ҿ�������� �������罺 (OJY : 09.03.25)
	cltBulletadjust ambersaurusAdjust( 0, 30,/**/-30, 20,/**/-40, 0,/**/-20, -35,/**/ 0, -40 );
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_DinoAmbersaurus.SPR"), NULL, ambersaurusAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_AMBERSAURUS].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC,
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �Ҿ�������� �Ѹ����װ� (OJY : 09.03.25)
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_DinoRollingStego.SPR"), NULL, DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_SCREEN, 0, 0 );
	BKI[BULLETKIND_ROLLINGSTEGO].Init(BLTSPEED(20), FALSE, FALSE,
		ATTACKTYPE_MAGIC,
		0,
		0, 50,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// ���� ���Ÿ����� ���Ǹ� - �ų�
	clLayerInfo.Init();
	clSoundInfo.Init();
	clDrawInfo.Set( TEXT("Bullet\\Bullet_FightingManRange.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_FIGHTINGMENRANGE].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_FIGHTINGMENRANGE,
		0,
		0, 0,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// �������Ǹ�(��) - ���Ÿ�
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAIRYRANGE_BULLET")),
		pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAIRYRANGE_HIT")) );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_FairyRange01.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_FAIRYRANGE].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_FAIRYRANGE,
		0,
		0, 0,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);
	//// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_ICERANGE_BULLET")),0 );
	clDrawInfo.Set( TEXT("Bullet\\Bullet_ICERANGE.SPR"), NULL, DefaultBulletAdjust, 0, 10, 0, false, TRANSPARENT_MODE_SCREEN,0,30,0 );
		BKI[BULLETKIND_SNOWQUEEN].Init(BLTSPEED(25), FALSE, FALSE,
		ATTACKTYPE_SNOWQUEEN,
		0,
		0, 1,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);


	//[����] ��ų��
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MAGIC_FLAMEBUSTER.SPR"), NULL, DefaultBulletAdjust, 0, 6, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_FLAMEBUSTER].Init(BLTSPEED(35), FALSE, FALSE,
									 ATTACKTYPE_MAGIC, 
									 0,
									 0, 0,
									 0, 0, 
									 &clSoundInfo,
									 &clLayerInfo,
									 &clDrawInfo	);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MAGIC_FLAMEWHIRL.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_FLAMEWHIRL].Init(BLTSPEED(35), FALSE, FALSE,
									ATTACKTYPE_MAGIC, 
									0,
									0, 0,
									0, 0, 
									&clSoundInfo,
									&clLayerInfo,
									&clDrawInfo		);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MAGIC_WETFOG.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_WETFOG].Init(BLTSPEED(35), FALSE, FALSE,
								ATTACKTYPE_MAGIC, 
								0,
								0, 0,
								0, 0, 
								&clSoundInfo,
								&clLayerInfo,
								&clDrawInfo		);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MAGIC_SLING.SPR"), NULL, DefaultBulletAdjust, 0, 7, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_SLING].Init( BLTSPEED(35), FALSE, FALSE,
								ATTACKTYPE_MAGIC, 
								0,
								0, 0,
								0, 0, 
								&clSoundInfo,
								&clLayerInfo,
								&clDrawInfo		);
	clLayerInfo.Init();
	clSoundInfo.Set( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_FIRE_FIREBALL")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BULLET_HIT_FIREBALL")) );
	clDrawInfo.Set( TEXT("Bullet\\MAGIC_WINDCUTER.SPR"), NULL, DefaultBulletAdjust, 0, 4, 0, true, TRANSPARENT_MODE_SCREEN, TRANSPARENT_MODE_SCREEN);
	BKI[BULLETKIND_WINDCUTER].Init( BLTSPEED(35), FALSE, FALSE,
									ATTACKTYPE_MAGIC, 
									0,
									0, 0,
									0, 0, 
									&clSoundInfo,
									&clLayerInfo,
									&clDrawInfo		);

	// [���] �Ȱ��̱� ���� - �����
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CLOWN_ATTACK")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CLOWN_BULLET1")));
	clDrawInfo.Set( TEXT("Bullet\\BULLET_CLOWN.SPR"), NULL, DefaultBulletAdjust, 0, 8, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_CLOWN].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_CLOWN,
		0,
		0, 0,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);

	// [���] �Ȱ��̱� ���� - �����(����)
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CLOWN_MAGIC")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_CLOWN_BULLET2")));
	clDrawInfo.Set( TEXT("Bullet\\Magic_CLOWN.SPR"), NULL, DefaultBulletAdjust, 0, 9, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_CLOWN_MAGIC].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC,
		0,
		0, 100,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);	

	// [���] �Ȱ��̱� ���� - �Ȱ��ź�
	clLayerInfo.Init();
	clSoundInfo.Set(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FOGBRIDE_MAGIC")), pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FOGBRIDE_BULLET")));
	clDrawInfo.Set( TEXT("Bullet\\MagicFOGBRIDE.SPR"), NULL, DefaultBulletAdjust, 0, 9, 0, true, TRANSPARENT_MODE_SCREEN );
	BKI[BULLETKIND_BOUQUET].Init(BLTSPEED(30), FALSE, FALSE,
		ATTACKTYPE_MAGIC,
		0,
		0, 0,
		0, 0, 
		&clSoundInfo,
		&clLayerInfo,
		&clDrawInfo
		);	
}
