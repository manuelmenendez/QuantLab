#ifndef EXCHANGE_H
#define EXCHANGE_H

namespace test
{
	template <typename C, typename T>  
	void Exchange(C object, void (C::* sf)(const T &), const T & (C::*gf)(), 
					void (C::* st)(const T &), const T & (C::*gt)())
	{
		BASE from = object.*gf();
		BASE to = object.*gt();

		object.*sf(to);
		object.*st(from);
	};

	template <typename C, typename T>
	void EX ( C * object, void (C::* sf)(const T &), const T & (C::*gf)() const,
				void (C::* st)(const T &), const T & (C::*gt)() const)
	{
		const T from = (*object.*gf)();
		T to = (*object.*gt)();

		(*object.*sf)(to);
		(*object.*st)(from);
	};
}

#endif
