<template>
  <q-card :class="elevated && 'shadow-8'">
    <q-card-section class="text-h6 text-blue-grey-8 text-weight-medium">
      {{ label }}
    </q-card-section>
    <q-separator />
    <q-card-section class="bg-grey-1">
      <slot />
    </q-card-section>
    <q-inner-loading :showing="loading">
      <q-spinner-gears
        size="140px"
        color="white"
      />
    </q-inner-loading>
  </q-card>
</template>

<script>
export default {
  name: 'Container',
  props: {
    label: {
      type: String,
    },
    elevated: {
      type: Boolean,
    },
    loading: {
      type: Boolean,
      default: false,
    },
  },
};
</script>

<style lang="sass" scoped>
</style>
