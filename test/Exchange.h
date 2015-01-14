#ifndef EXCHANGE_H
#define EXCHANGE_H


	namespace test
	{
		//Exchange two attributes different of an object, using its accesors
		template <typename C, typename T>
		void Exchange(C * object, void (C::* sf)(const T &), const T & (C::*gf)() const,
			void (C::* st)(const T &), const T & (C::*gt)() const)
		{
				Exchange<C, C, T>(object, object, sf, gf, st, gt);

		};

		//Exchange two attributes of two objects, , using its accesors
		template <typename C1, typename C2, typename T> inline
			void Exchange(C1 * object1, C2 * object2, void (C1::* sf)(const T &), const T & (C1::*gf)() const,
			void (C2::* st)(const T &), const T & (C2::*gt)() const)
		{
				const T from = (*object1.*gf)();
				T to = (*object2.*gt)();

				(*object1.*sf)(to);
				(*object2.*st)(from);
		};
	
}

#endif
