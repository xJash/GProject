//=======================================================================
// NkRTTI, NkCaster
//=======================================================================
/*
	created:	2009/09/
	author:		�����(CHO MYEONG GEUN), narlamy@ndoors.net
	purpose:	native c++�� dynamic casting �ӵ��� ����� ������
				���� ������ ó���ϱ� ���ؼ� ���۵�

				��ũ��Ʈ �� �ܺ� ����Ÿ�� ������ �ڵ�ȭ ó���� ���, 
				�����ϰ� ���� �� ����
	update:						
	note:		���Ӻ긮�� RTTI�� ������� ��ũ�� �Լ��� ������� �ʰ�
				��ü�� ĳ���� �޼ҵ带 ������ �ֵ��� �������̽� ����				
*/
//=======================================================================

#pragma once

//------------------------------------------------------------------------------
// NkRTTI (run-time type information)
//------------------------------------------------------------------------------
class NkRTTI
{
public:
    NkRTTI (const char* pcName, const NkRTTI* pkBaseRTTI);

    const char*			GetName() const;
    const NkRTTI*		GetBaseRTTI() const;

    bool				CopyName(char* acNameBuffer, unsigned int uiMaxSize) const;

protected:
    const char*			m_pcName;
    const NkRTTI*		m_pkBaseRTTI;
};

//------------------------------------------------------------------------------
// insert in root class declaration
//------------------------------------------------------------------------------
#define NkDeclareRootRTTI(classname) \
    public: \
        static  const NkRTTI	ms_RTTI; \
        virtual const NkRTTI*	GetRTTI() const		{return &ms_RTTI;} \
		static  const char*		TypeName()			{return ms_RTTI.GetName();}\
		static  const TYPE		Type() 				{return &ms_RTTI; } \
		static  const char*		TypePreWord()		{return #classname; } \
		\
        static bool IsExactKindOf(const NkRTTI* pkRTTI, \
            const NkCaster* pkObject) \
        { \
            if (!pkObject) \
            { \
                return false; \
            } \
            return (pkObject->GetRTTI()==pkRTTI); \
        } \
        static bool IsKindOf(const NkRTTI* pkRTTI, \
            const NkCaster* pkObject) \
        { \
            if (!pkObject) \
            { \
                return false; \
            } \
            \
            const NkRTTI* pkTmp = pkObject->GetRTTI(); \
            while (pkTmp) \
            { \
                if (pkTmp == pkRTTI) \
                { \
                    return true; \
                } \
                pkTmp = pkTmp->GetBaseRTTI(); \
            } \
            return false; \
        } \
        static classname* VerifyStaticCastDebug(const NkRTTI* pkRTTI, \
            const NkCaster* pkObject) \
        { \
            if (!pkObject) \
            { \
                return 0x00; \
            } \
            classname* pkDynamicCast = DynamicCast(pkRTTI, pkObject); \
            return pkDynamicCast; \
        } \
        static classname* DynamicCast(const NkRTTI* pkRTTI, \
            const NkCaster* pkObject) \
        { \
            if (!pkObject) \
            { \
                return 0x00; \
            } \
            return (IsKindOf(pkRTTI,pkObject) ? (classname*) pkObject : 0 ); \
        }

//------------------------------------------------------------------------------
// insert in class declaration
//------------------------------------------------------------------------------
#define NkDeclareRTTI \
    public: \
        static  const NkRTTI	ms_RTTI; \
        virtual const NkRTTI*	GetRTTI() const		{return &ms_RTTI;} \
		static  const char*		TypeName()			{return ms_RTTI.GetName();} \
		static  const TYPE		Type()				{return &ms_RTTI; }

//------------------------------------------------------------------------------
// insert in root class source file
//------------------------------------------------------------------------------
#define NkImplementRootRTTI(rootclassname) \
    const NkRTTI rootclassname::ms_RTTI(#rootclassname, 0)

//------------------------------------------------------------------------------
// insert in class source file
//------------------------------------------------------------------------------
#define NkImplementRTTI(classname, baseclassname) \
    const NkRTTI classname::ms_RTTI(#classname, &baseclassname::ms_RTTI)


//------------------------------------------------------------------------------
// Caster
//------------------------------------------------------------------------------
class NkCaster
{
public:
	typedef	const NkRTTI*		TYPE;

	// get RTTI object instance
	virtual const NkRTTI*		GetRTTI() const = 0;

	// get TypeName of current instance
	const char*					GetTypeName() const;
	const TYPE					GetType() const;
	
	const bool					IsSameExactType(const TYPE kType) const;
	const bool					IsSameType(const TYPE kType) const;
	
	// macros for run-time type testing
	template <class T> bool		IsSameExactKind();
	template <class T> bool		IsSameKind();
	
	// macro for compile time type casting
	template <class T> T*		StaticCast();

	// macro for compile time type casting, with debug run-time assert
	template <class T> T*		VerifyStaticCast();

	// macro for run-time type casting, returns NULL if invalid cast
	template <class T> T*		DynamicCast();
	template <class T> T*		ConvertTo();	// DynamicCast()�� ����
};

//------------------------------------------------------------------------------
// Sample 1: using
//------------------------------------------------------------------------------
/*
	<����>

	1-1. RTTI�� �����ϰ� ���� Ŭ������ NkCaster�� ��ӹް�
	NkDeclareRootRTTI() ��ũ�θ� Ŭ�����ȿ� ����

	1-2. �ҽ��ڵ� �����ο� NkImplementRootRTTI() ��ũ�� ����

	2-1. NkCaster�� ��ӹ޾� ������ Ŭ������ �ٽ� ��ӹ޾Ƽ�
	�߰� casting�� �����ϰ� �������� NkDeclareRTTI() 
	��ũ�θ� Ŭ�����ȿ� ����

	2-2. �ҽ��ڵ� �����ο� NkImplementRTTI() ��ũ�� ����


	<�ڵ�ȭ>

	NkRTTI�� NkCaster�� ��ӹ��� �ν��Ͻ��� Ÿ���� �˾ƿ��� 
	NkCaster::GetType() �޼ҵ�� NkDeclareRootRTTI���� �����ϴ�
	Type() �޼ҵ带 Ȱ���ؼ� �߻� ��ü ����Ʈ���� �˻��� �����ϰ�
	���ݴϴ�.

	GetRTTI()�� ms_RTTI�� ���� �����Ͽ� ó�� �� ���� ������,
	�̸��� �� �� ���ϰ� �����մϴ�.

	class NkPropety : public NkCaster
	{
		// 
	};

	class NkPropetyScale : public NkProperty
	{
		//
	};

	class NkPropetyRotation : public NkProperty
	{
		//
	};

	class NkPropetyColor : public NkProperty
	{
		//
	};

	NkProperty* GetProperty(NkProperty::TYPE kType)
	{
		typedef std::list<NkPrperty*> Properties;
		Properties kList;

		Properties::iterator it = kList.begin();
		Properties::iteartor end = kList.end();

		for(; it!=end; it++)
		{
			NkPrperty* pkProperty = *it;
			if(pkProperty->GetType()==kType)
			{
				return pkProperty;
			}
		}
		return NULL;
	}

	void Sample()
	{
		NkProperty* pkProperty = GetProperty(NkPropertyScale::Type());
		if(pkProperty)
		{
			//
		}
	}
*/

//------------------------------------------------------------------------------
// Sample 2: Casting
//------------------------------------------------------------------------------
/*
class A : public NkCaster
{
public:
	NkDeclareRootRTTI(A);

	virtual void Print()
	{
		printf("A\n");
	}
};

class B : public A
{
public:
	NkDeclareRTTI();

	virtual void Print()
	{
		printf("B\n");
	}
};

class C : public A
{
public:
	NkDeclareRTTI();

	virtual void Print()
	{
		printf("C\n");
	}
};

NkImplementRootRTTI(A);
NkImplementRTTI(B,A);
NkImplementRTTI(C,A);

void Sample()
{
	printf("==============================\n");
	printf("A=\"%s\", B=\"%s\", C=\"%s\"\n", A::TypeName(), B::TypeName(), C::TypeName());
	printf("==============================\n");

	A a;
	a.Print();

	B b;
	b.Print();

	C c;
	c.Print();

	A* p1 = &b;
	A* p2 = &c;

	if(p1->IsSameType<A>()) printf("p1==A\n");
	else printf("p!=A\n");

	if(p1->IsSameType<B>()) printf("p1==B\n");
	else printf("p!=B\n");

	if(p2->IsSameType<A>()) printf("p2==A\n");
	else printf("p2!=A\n");

	if(p2->IsSameType<B>()) printf("p2==B\n");
	else printf("p2!=B (p2=\"%s\")\n", p2->GetTypeName());
}
*/

//------------------------------------------------------------------------------
// macros for run-time type testing
//------------------------------------------------------------------------------
#define NkIsExactKindOf(classname, pkObject) \
	classname::IsExactKindOf(&classname::ms_RTTI, pkObject)

//------------------------------------------------------------------------------
// macros for run-time type testing
//------------------------------------------------------------------------------
#define NkIsKindOf(classname, pkObject) \
	classname::IsKindOf(&classname::ms_RTTI, pkObject)

//------------------------------------------------------------------------------
// macro for compile time type casting
//------------------------------------------------------------------------------
#define NkStaticCast(classname, pkObject) \
	 ((classname*) pkObject)

//------------------------------------------------------------------------------
// macro for compile time type casting, with debug run-time assert
//------------------------------------------------------------------------------
#ifdef NkDEBUG
	#define NiVerifyStaticCast(classname, pkObject) \
			((classname*) classname::VerifyStaticCastDebug( \
				&classname::ms_RTTI, pkObject))
#else
	#define NiVerifyStaticCast(classname, pkObject) ((classname*) (pkObject))
#endif

//------------------------------------------------------------------------------
// macro for run-time type casting, returns NULL if invalid cast
//------------------------------------------------------------------------------
#define NkDynamicCast(classname, pkObject) \
	((classname*) classname::DynamicCast(&classname::ms_RTTI, pkObject))

//------------------------------------------------------------------------------

#include "NkRTTI.inl"