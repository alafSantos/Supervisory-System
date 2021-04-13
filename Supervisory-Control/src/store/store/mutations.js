
export function logout(state) {
  state.user = undefined;
  localStorage.clear();
}

export function setScreen(state, payload) {
  state.screen = payload;
}

export function setUser(state, payload) {
  state.user = payload;
}
