export async function loginUser(context, state) {
  context.commit('setUser', state.user);
  localStorage.setItem(process.env.storage, state.access_token);
}

export function logoutUser(context) {
  context.commit('logout');
}

export function setScreen(context, state) {
  context.commit('setScreen', state);
}
