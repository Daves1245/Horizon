#ifndef CUP_BIT_MANIPULATION
#define CUP_BIT_MANIPULATION

/* Is the bit at i on */
#define is_on(b, i) (b & (1 << i))
/* Grab least significant one */
#define ls_one(b) (b & (-b))
/* Set the bit at i on */
#define set(b, i) (b |= (1 << i))
/* Clear the bit at i */
#define clear(b, i) (b &= ~(1 << i))
/* Set the least siginificant one off */
#define last_one_off(b) ((b) & (b - 1))
/* Set the last zero on */
#define last_zero_on(b) ((b) | (b + 1))
/* Toggle the bit at i */
#define toggle(b, i) (b ^= (1 << i))
/* Set all lower n bits on */
#define set_all(b, n) (b = (1 << n) - 1)
/* Grab the modulo */
#define modulo(b, n) ((b) & (n - 1))
/* Is b a power of two */
#define is_power_of_two(b) (!(b & (b - 1)))

#endif
