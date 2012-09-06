#ifndef normal_h
#define normal_h

	class Normal 
	{
		public:
				Normal();
				~Normal();
			float	Get_N1();
			float	Get_N2();
			float	Get_N3();
			void	Set_N1(float n1);
			void	Set_N2(float n2);
			void	Set_N3(float n3);
		private:
			float	n1;
			float	n2;
			float	n3;
	};
#endif
