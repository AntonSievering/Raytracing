#pragma once
#include <cstdint>
#include <cmath>
#include <glm/glm.hpp>
#include "vec2d.h"

namespace Engine
{
	template <class T>
	struct vec3d
	{
	public:
		T x = T();
		T y = T();
		T z = T();

	public:
		inline vec3d()                                               noexcept { x = T(); y = T(); z = T();                                                               }
		inline vec3d(const T &_x, const T &_y, const T &_z)          noexcept { x = _x; y = _y; z = _z;                                                                  }
		inline vec3d(const vec3d &v)                                 noexcept { x = v.x; y = v.y; z = v.z;                                                               }
		inline vec3d(const glm::vec3 &v)                             noexcept { x = v.x; y = v.y; z = v.z;                                                               }

	public:
		constexpr inline T      mag()                          const noexcept
		{
			T f = mag2();
			return std::sqrt(f);
		}
		constexpr inline T      mag2()                         const noexcept { return           x * x + y * y + z * z;                                                  }

		constexpr inline vec3d  norm()                         const noexcept
		{
			T r = T(1) / mag();
			return vec3d(x * r, y * r, z * r);
		}
		constexpr inline vec3d  normalize()                          noexcept { T r = T(1) / mag(); x *= r; y *= r; z *= r; return *this;                                }
		constexpr inline vec3d  perp()                         const noexcept { return vec3d(-y, x, 0);                                                                  }

		constexpr inline T      dot  (const vec3d &rhs)        const noexcept { return x * rhs.x + y * rhs.y + z * rhs.z;                                                }
		constexpr inline vec3d  cross(const vec3d &rhs)        const noexcept { return vec3d(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);       }

		constexpr inline vec3d  abs()                          const noexcept { return vec3d(std::abs(x), std::abs(y), std::abs(z));                                     }
		constexpr inline vec3d  floor()                        const noexcept { return vec3d(std::floor(x), std::floor(y), std::floor(z));                               }
		constexpr inline vec3d  ceil()                         const noexcept { return vec3d(std::ceil(x),  std::ceil(y),  std::ceil(z));                                }
		constexpr inline vec3d  inv()                          const noexcept { return vec3d(1.0f / x, 1.0f / y, 1.0f / z);                                              }

	public:
		constexpr inline vec2d<T>  xy()                        const noexcept { return vec2d<T>(x, y);                                                                   }
		constexpr inline vec2d<T>  yz()                        const noexcept { return vec2d<T>(y, z);                                                                   }
		constexpr inline vec2d<T>  xz()                        const noexcept { return vec2d<T>(x, z);                                                                   }
		
	public:
		constexpr inline vec3d  operator +  (const vec3d &rhs) const noexcept { return vec3d(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);                         }
		constexpr inline vec3d  operator -  (const vec3d &rhs) const noexcept { return vec3d(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);                         }
		constexpr inline vec3d  operator *  (const T     &rhs) const noexcept { return vec3d(this->x * rhs,   this->y * rhs,   this->z * rhs  );                         }
		constexpr inline vec3d  operator *  (const vec3d &rhs) const noexcept { return vec3d(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);                         }
		constexpr inline vec3d  operator /  (const T     &rhs) const noexcept { return vec3d(this->x / rhs,   this->y / rhs,   this->z / rhs  );                         }
		constexpr inline vec3d  operator /  (const vec3d &rhs) const noexcept { return vec3d(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);                         }

		constexpr inline vec3d &operator += (const vec3d &rhs)       noexcept { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this;                      }
		constexpr inline vec3d &operator -= (const vec3d &rhs)       noexcept { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this;                      }
		constexpr inline vec3d &operator *= (const T     &rhs)       noexcept { this->x *= rhs;   this->y *= rhs;   this->z *= rhs;   return *this;                      }
		constexpr inline vec3d &operator /= (const T     &rhs)       noexcept { this->x /= rhs;   this->y /= rhs;   this->z /= rhs;   return *this;                      }

	public:
		constexpr inline bool   operator == (const vec3d &rhs) const noexcept { return rhs.x == x && rhs.y == y && rhs.z == z;                                           }
		constexpr inline bool   operator != (const vec3d &rhs) const noexcept { return !operator==(rhs);                                                                 }

	public:
		constexpr inline vec3d operator+()                     const noexcept { return *this;                                                                            }
		constexpr inline vec3d operator-()                     const noexcept { return vec3d<T>(-x, -y, -z);                                                             }

	public:
		template <class _T>
		constexpr inline operator vec3d<_T>()                  const noexcept { return { static_cast<_T>(this->x), static_cast<_T>(this->y), static_cast<_T>(this->z) }; }
		constexpr inline operator glm::vec3()                  const noexcept { return glm::vec3(x, y, z);                                                               }
	};

	using vs3d = vec3d<short>;
	using vi3d = vec3d<int32_t>;
	using vu3d = vec3d<uint32_t>;
	using vf3d = vec3d<float>;
	using vd3d = vec3d<double>;
}
