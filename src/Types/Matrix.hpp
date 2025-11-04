#pragma once

template <std::size_t N, std::size_t M, typename T = float>
struct Matrix
{
	T m[N][M];

	Matrix() {
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				m[i][j] = T(0);
	}
};