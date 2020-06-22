/* App4 S6 
 * Fait par: -Thierry Constantin (cont3301)
 *           -Gabriel Lessard    (lesg2605)
 */

#ifndef NEW_H
#define NEW_H

#include <stddef.h>

void* operator new(size_t, void* ptr);  /* placement new */

#endif  /* NEW_H */