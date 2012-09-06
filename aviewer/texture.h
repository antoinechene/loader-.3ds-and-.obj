#ifndef texture_h
#define texture_h

	class Texture
	{
		public:
			Texture();
			~Texture();
			float	Get_U();
			float	Get_V();
			void	Set_U(float u);
			void	Set_V(float v);
		private:
			float	u;
			float	v;
	};
#endif
