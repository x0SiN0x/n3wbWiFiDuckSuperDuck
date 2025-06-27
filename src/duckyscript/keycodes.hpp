#pragma once

// Layout dispatcher
#if defined(OPT_KEYBOARD_LAYOUT_US)
  #include "locale/layout_us.hpp"
#elif defined(OPT_KEYBOARD_LAYOUT_UK)
  #include "locale/layout_uk.hpp"
#else
  #error "No keyboard layout defined!"
#endif
