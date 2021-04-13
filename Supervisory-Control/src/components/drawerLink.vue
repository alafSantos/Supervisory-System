<template>
  <q-item
    @mouseover="highlight = true"
    @mouseleave="highlight = false"
    :class="this.active || this.highlight ? 'item highlight q-ma-sm' : 'text-blue-4 item q-ma-sm'"
    :to="link"
  >
    <q-item-section
      v-if="icon"
      avatar
    >
      <q-icon :name="icon" />
    </q-item-section>

    <q-item-section>
      <q-item-label>{{ title }}</q-item-label>
      <q-item-label caption class="text-grey-2">
        {{ caption }}
      </q-item-label>
    </q-item-section>
  </q-item>
</template>

<script>
export default {
  name: 'DrawerLink',
  data() {
    return {
      highlight: false,
    };
  },
  props: {
    title: {
      type: String,
      required: true,
    },
    caption: {
      type: String,
      default: '',
    },
    link: {
      type: [String, Object],
      default: '#',
    },
    icon: {
      type: String,
      default: '',
    },
  },
  computed: {
    active() {
      const screen = this.$store.getters['MainStore/getScreen'];
      if (screen === this.title) return true;
      return false;
    },
  },
};
</script>

<style lang="sass" scoped>
.item
  border-radius: 10px

.highlight
  color: white
  background-color: rgba(255, 255, 255, 0.20)
</style>
