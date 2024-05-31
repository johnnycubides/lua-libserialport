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
  if (!lua_istable(L, 2)) {
    lua_pushnil(L);
    lua_pushstring(L, "Options must be a table {}");
    return 2;
  }
  if (sp_get_port_by_name(port_name, &port) != SP_OK) {
    lua_pushnil(L);
    lua_pushstring(L, "Failed get_port_by_name");
    return 2;
  }
  // Valores por default
  int baudrate = 115200;
  int bits = 8;
  int parity = SP_PARITY_NONE;
  int stopbits = 1;
  int flowcontrol = SP_FLOWCONTROL_NONE;
  int dtr = SP_DTR_INVALID;
  int rts = SP_RTS_INVALID;
  int cts = SP_CTS_IGNORE;

  lua_getfield(L, 2, "baudRate");
  if (lua_isnumber(L, -1)) {
    baudrate = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "bits");
  if (lua_isnumber(L, -1)) {
    bits = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "parity");
  if (lua_isnumber(L, -1)) {
    parity = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "stopBits");
  if (lua_isnumber(L, -1)) {
    stopbits = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "flowControl");
  if (lua_isnumber(L, -1)) {
    flowcontrol = lua_tointeger(L, -1);
    switch (lua_tointeger(L, -1)) {
    case 0:
      flowcontrol = SP_FLOWCONTROL_NONE;
      break;
    case 1:
      flowcontrol = SP_FLOWCONTROL_XONXOFF;
      break;
    case 2:
      flowcontrol = SP_FLOWCONTROL_RTSCTS;
      break;
    case 3:
      flowcontrol = SP_FLOWCONTROL_DTRDSR;
      break;
    default:
      break;
    }
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "dtr");
  if (lua_isnumber(L, -1)) {
    switch (lua_tointeger(L, -1)) {
    case 0:
      dtr = SP_DTR_OFF;
      break;
    case 1:
      dtr = SP_DTR_ON;
      break;
    case 2:
      dtr = SP_DTR_FLOW_CONTROL;
      break;
    case -1:
      dtr = SP_DTR_INVALID;
      break;
    default:
      break;
    }
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "rts");
  if (lua_isnumber(L, -1)) {
    switch (lua_tointeger(L, -1)) {
    case 0:
      rts = SP_RTS_OFF;
      break;
    case 1:
      rts = SP_RTS_ON;
      break;
    case 2:
      rts = SP_RTS_FLOW_CONTROL;
      break;
    case -1:
      rts = SP_RTS_INVALID;
      break;
    default:
      break;
    }
  }
  lua_pop(L, 1);

  lua_getfield(L, 2, "cts");
  if (lua_isnumber(L, -1)) {
    switch (lua_tointeger(L, -1)) {
    case 0:
      sp_set_cts(port, SP_CTS_IGNORE);
      break;
    case 1:
      sp_set_cts(port, SP_CTS_FLOW_CONTROL);
      break;
    case -1:
      sp_set_cts(port, SP_CTS_INVALID);
      break;
    default:
      break;
    }
  }
  lua_pop(L, 1);

  if (sp_open(port, SP_MODE_READ_WRITE) == SP_OK) {
    if (sp_set_baudrate(port, baudrate) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set baudrate");
      return 2;
    }

    if (sp_set_bits(port, bits) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set bits");
      return 2;
    }

    if (sp_set_parity(port, parity) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set parity");
      return 2;
    }

    if (sp_set_stopbits(port, stopbits) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set stopbits");
      return 2;
    }

    if (sp_set_parity(port, parity) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set parity");
      return 2;
    }

    if (sp_set_stopbits(port, stopbits) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set stopbits");
      return 2;
    }

    if (sp_set_flowcontrol(port, flowcontrol) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set flowcontrol");
      return 2;
    }

    if (sp_set_dtr(port, dtr) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set baudrate");
      return 2;
    }

    if (sp_set_rts(port, rts) != SP_OK) {
      lua_pushnil(L);
      lua_pushstring(L, "Failed to set rts");
      return 2;
    }
    // Realizar un flush
    sp_flush(port, SP_BUF_BOTH);
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
  if (sp_close(port) != SP_OK) {
    lua_pushnil(L);
    return 1;
  } else {
    sp_free_port(port);
    lua_pushinteger(L, 1);
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
    buffer[result] = '\0';
    lua_pushstring(L, buffer);
    lua_pushinteger(L, result);
  } else {
    lua_pushnil(L);
    lua_pushinteger(L, result);
  }
  free(buffer);
  return 2;
}

static int l_flush_to_port(lua_State *L) {
  struct sp_port *port = lua_touserdata(L, 1);
  enum sp_buffer flush = SP_BUF_INPUT;
  switch (luaL_checkinteger(L, 2)) {
  case 1:
    flush = SP_BUF_INPUT;
    break;
  case 2:
    flush = SP_BUF_OUTPUT;
    break;
  case 3:
    flush = SP_BUF_BOTH;
    break;
  default:
    break;
  }
  enum sp_return result = sp_flush(port, flush);
  lua_pushinteger(L, result);
  return 1;
}

static const struct luaL_Reg libserial[] = {{"list_ports", l_list_port},
                                            {"open", l_open_port},
                                            {"read", l_read_to_port},
                                            {"write", l_write_to_port},
                                            {"flush", l_flush_to_port},
                                            {"close", l_close_port},
                                            {NULL, NULL}};

int luaopen_libserial(lua_State *L) {
  luaL_newlib(L, libserial);
  return 1;
}
