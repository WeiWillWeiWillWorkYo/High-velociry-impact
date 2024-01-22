#include <iostream>
#include "datatypes.h"
#include "particles.h"
#include "kernel.h"
using namespace std;
using namespace physics;

int main()
{
	particles_t myParticles = newParticles();

	// 设置粒子的属性
	double x = 1.0;    // x坐标
	double y = 2.0;    // y坐标
	double vx = 0.5;   // x方向的速度
	double vy = 0.5;   // y方向的速度
	double m = 1.0;    // 质量
	double rho_0 = 1000.0; // 初始密度
	double h_size = 1.0;   // 平滑尺寸

	// 添加一个新的粒子
	addParticle(myParticles, x, y, vx, vy, m, rho_0, h_size);
	addParticle(myParticles, x + 0.1, y + 0.1, vx, vy, m, rho_0, h_size);

	double dist[DIM];
	double m_dist = 0.0;
	for (int d = 0; d < DIM; ++d) {
		dist[d] = myParticles.particle[0].r[d] - myParticles.particle[1].r[d];
		m_dist += dist[d] * dist[d];
	}
	m_dist = sqrt(m_dist);

	// 创建交互对
	int_pair_t interaction;
	interaction.i = 0;  // 第一个粒子的索引
	interaction.j = 1;  // 第二个粒子的索引

	// 初始化int_pairs_t对象
	int_pairs_t intPairs = newIntPairs();

	// 添加交互对到intPairs对象的int_pair向量中
	intPairs.int_pair.push_back(interaction);

	// 使用kernel函数计算权重和梯度
	// 注意我们现在传递intPairs.int_pair[0]的引用给kernel函数
	kernel(m_dist, dist, intPairs.int_pair[0], h_size);
	// 使用kernel函数计算权重和梯度

	// 打印结果
	std::cout << "Weight: " << intPairs.int_pair[0].w << std::endl;
	std::cout << "Gradient: (" << intPairs.int_pair[0].dwdx[0] << ", " << intPairs.int_pair[0].dwdx[1] << ")" << std::endl;

	// 打印第一个粒子的密度
	cout << "密度: " << myParticles.particle[0].rho << endl;

	return 0;
}