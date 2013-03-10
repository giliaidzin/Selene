#ifndef SE_APP_MODULE_H
#define SE_APP_MODULE_H

#include "Selene/Utils/seUtils.h"

namespace Selene
{

	class CSupervisor;

	class IAppModule
	{
	public:
		IAppModule()
			:m_ID(-1)
			,m_pSupervisor(NULL)
		{}
		virtual ~IAppModule() {}

		virtual void Init() = 0;
		virtual void Terminate() = 0;
		virtual void Reset() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual bool Finished() = 0;

		inline void SetID(int id);
		inline void SetSupervisor(CSupervisor* pSupervisor);
		inline int GetID() const;
		inline CSupervisor* GetSupervisor() const;

	private:
		int m_ID;
		CSupervisor* m_pSupervisor;
	};

	// inline functions
	inline void IAppModule::SetID(int id)
	{
		m_ID = id;
	}
	inline void IAppModule::SetSupervisor(CSupervisor* pSupervisor)
	{
		m_pSupervisor = pSupervisor;
	}
	inline int IAppModule::GetID() const
	{
		return m_ID;
	}
	inline CSupervisor* IAppModule::GetSupervisor() const
	{
		return m_pSupervisor;
	}

}

#endif // SE_APP_MODULE_H
