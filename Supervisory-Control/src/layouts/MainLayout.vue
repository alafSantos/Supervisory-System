<template>
  <q-layout view="hHh lpR fFf">
    <div class="q-pa-md">
    <q-btn
      color="primary"
      @click="$q.fullscreen.toggle()"
      :icon="$q.fullscreen.isActive ? 'fullscreen_exit' : 'fullscreen'"
      :label="$q.fullscreen.isActive ? 'ON' : 'OFF'"
    />
    </div>
    <q-page-container class="fixed-center">
      <router-view />
    </q-page-container>

  </q-layout>
</template>

<script>
export default {
  data() {
    return {
    };
  },
};
</script>

<style lang="scss" scoped>

</style>
