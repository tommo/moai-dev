#ifndef MOAISTEERBEHAVIOUR_H
#define MOAISTEERBEHAVIOUR_H

#include "moai-sim/headers.h"

#include "MOAISteerLimiter.h"

class MOAISteerController;
class MOAISteerBehaviourGroup;

//----------------------------------------------------------------//
//----------------------------------------------------------------//
struct MOAISteerAcceleration {
	public:
		ZLVec3D mLinear;
		float   mAngular;

		GET_SET( ZLVec3D, Linear,  mLinear  );
		GET_SET( float,   Angular, mAngular );

		MOAISteerAcceleration() : mLinear( 0.0f, 0.0f, 0.0f ), mAngular( 0.0f ) {};

		bool IsZero () {
			return 
				this->mLinear.LengthSqrd() < EPSILON
				&& this->mAngular < EPSILON;
		};

		void Reset () {
			this->mLinear.Init( 0.0f, 0.0f, 0.0f );
			this->mAngular = 0.0f;
		};

		void Add( const MOAISteerAcceleration& acc ) {
			this->mLinear.Add( acc.mLinear );
			this->mAngular += acc.mAngular;
		};

		void Add( const MOAISteerAcceleration& acc, float scl ) {
			this->mLinear.Add( acc.mLinear, scl );
			this->mAngular += acc.mAngular * scl;
		};

		void Scale( float scl ) {
			this->mLinear.Scale( scl );
			this->mAngular *=  scl;
		};

		float LengthSqrd() {
			return this->mLinear.LengthSqrd() + this->mAngular * this->mAngular;
		};

		float Length() {
			return sqrtf( this->LengthSqrd() );
		};

		void Init( const MOAISteerAcceleration& acc ) {
			this->mLinear.Init( acc.mLinear );
			this->mAngular = acc.mAngular;
		};

		void Init( const ZLVec3D& linear, float angular ) {
			this->mLinear.Init( linear );
			this->mAngular = angular;
		};
};


//----------------------------------------------------------------//
//----------------------------------------------------------------//
class MOAISteerBehaviour:
	public MOAINode
{
private:
	friend class MOAISteerController;	
	friend class MOAISteerBehaviourGroup;	

	static int _getOwner      ( lua_State* L );
	static int _getParent     ( lua_State* L );
	static int _getWeight     ( lua_State* L );
	static int _setWeight     ( lua_State* L );

	static int _setLimiter    ( lua_State* L );
	static int _getLimiter    ( lua_State* L );

protected:
	//----------------------------------------------------------------//
	MOAISteerBehaviour* mParent;
	MOAILuaSharedPtr < MOAISteerLimiter >  mLimiter;

	float mWeight;
	bool  mEnabled;

public:
	virtual void OnInit () {};	

	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
		return false;
	};

	virtual MOAISteerController* GetOwner() { 
		if( !this->mParent ) return NULL;
		return this->mParent->GetOwner();
	};

	virtual bool OnReportNeighbor ( MOAISteerController* neighbor ) {
		return false;
	};

	MOAISteerLimiter* GetActualLimiter();
	void SetLimiter( MOAISteerLimiter* limiter );

	GET     ( MOAISteerBehaviour*, Parent, mParent )
	GET_SET ( float, Weight,  mWeight )

	SET     ( bool,  Enabled, mEnabled )
	IS      ( Enabled, mEnabled, true )

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviour )

	MOAISteerBehaviour();
	~MOAISteerBehaviour();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};

#endif