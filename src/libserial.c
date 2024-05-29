#include "./include/libserialport.h"
#include "./lib/lua/lauxlib.h"
#include "./lib/lua/lua.h"
#include "lib/lua/lualib.h"

static int l_open_port(lua_State *L) {
  const char *port_name = luaL_checkstring(L, 1);
  struct sp_port *port;
  sp_get_port_by_name(port_name, &port);
  if (sp_open(port, SP_MODE_READ_WRITE) != SP_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "Failed to open port");
    return 2;
  }
  lua_pushlightuserdata(L, port);
  return 1;
}

static const struct luaL_Reg libserial[] = {{"open", l_open_port},
                                            {NULL, NULL}};
int luaopen_libserial(lua_State *L) {
  luaL_newlib(L, libserial);
  return 1;
}
