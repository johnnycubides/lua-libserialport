#include "./include/libserialport.h"
#include "./lib/lua/lauxlib.h"
#include "./lib/lua/lua.h"
#include <stdlib.h>
#include <string.h>
// #include "lib/lua/lualib.h"

static int l_list_port(lua_State *L) {
  struct sp_port **port_list;
  enum sp_return result = sp_list_ports(&port_list);
  if (result != SP_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "List port failed");
    return 2;
  }
  lua_newtable(L);
  for (int i = 0; port_list[i] != NULL; i++) {
    lua_pushnumber(L, i + 1);
    lua_pushstring(L, sp_get_port_name(port_list[i]));
    lua_settable(L, -3);
  }
  /* Free the array created by sp_list_ports(). */
  sp_free_port_list(port_list);
  return 1;
}

static int l_open_port(lua_State *L) {
  const char *port_name = luaL_checkstring(L, 1);
  struct sp_port *port;
  if (sp_get_port_by_name(port_name, &port) != SP_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "Failed get_port_by_name");
    return 2;
  }
  if (sp_open(port, SP_MODE_READ_WRITE) == SP_OK) {
    sp_set_baudrate(port, 115200);
    sp_set_bits(port, 8);
    sp_set_parity(port, SP_PARITY_NONE);
    sp_set_stopbits(port, 1);
    sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);
    lua_pushlightuserdata(L, port);
    return 1;
  } else {
    lua_pushnil(L);
    lua_pushstring(L, "Failed to open port");
    return 2;
  }
}

static int l_close_port(lua_State *L) {
  struct sp_port *port = lua_touserdata(L, 1);
  if (sp_close(port) == SP_OK) {
    sp_free_port(port);
    lua_pushinteger(L, 1);
    return 1;
  } else {
    lua_pushnil(L);
    return 1;
  }
}

static int l_write_to_port(lua_State *L) {
  struct sp_port *port = lua_touserdata(L, 1);
  const char *data = luaL_checkstring(L, 2);
  const int timeout_ms = luaL_checkinteger(L, 3);
  int result = sp_blocking_write(port, data, strlen(data), timeout_ms);
  lua_pushinteger(L, result);
  return 1;
}

static int l_read_to_port(lua_State *L) {
  struct sp_port *port = lua_touserdata(L, 1);
  const int size = luaL_checkinteger(L, 2);
  const int timeout_ms = luaL_checkinteger(L, 3);
  /* Allocate a buffer to receive data. */
  char *buffer = malloc(size + 1);
  int result = sp_blocking_read(port, buffer, size, timeout_ms);
  if (result > 0) {
    lua_pushlstring(L, buffer, result);
  } else {
    lua_pushnil(L);
    lua_pushinteger(L, result);
  }
  free(buffer);
  return 1;
}

static const struct luaL_Reg libserial[] = {{"list_ports", l_list_port},
                                            {"open", l_open_port},
                                            {"write", l_write_to_port},
                                            {"close", l_close_port},
                                            {NULL, NULL}};

int luaopen_libserial(lua_State *L) {
  luaL_newlib(L, libserial);
  return 1;
}
