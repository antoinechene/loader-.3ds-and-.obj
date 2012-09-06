#ifndef vertex_h
#define vertex_h

	class Vertex
	{
		public:
				Vertex();
				~Vertex();
			float	Get_X();
			float	Get_Y();
			float	Get_Z();
			void	Set_X(float x);
			void	Set_Y(float y);
			void	Set_Z(float z);
		private:
			float	x;
			float	y;
			float	z;
	};
#endif
