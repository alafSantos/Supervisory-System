<template>
  <q-card
    class="shadow-8"
    :style="borderColor ? `border-left: .25rem solid ${borderColor} !important;` : ''"
  >
    <q-card-section horizontal class="row">
      <q-card-section
        class="col-xs-8 justify-center"
      >
        <div class="col">
        <!-- Title -->
        <div :class="`text-subtitle1 text-weight-medium text-${color}`">
          {{ title }}
        </div>
        <!-- Value -->
        <div>
          <slot name="content" />
        </div>
        </div>
      </q-card-section>
      <q-card-section
        class="col-xs-4 content-center text-right"
      >
        <!-- Icon -->
        <q-icon
          :name="icon"
          class="text-blue-grey-2"
          size="lg"
        />
      </q-card-section>
    </q-card-section>
  </q-card>
</template>

<script>
export default {
  name: 'CardBadge',
  props: {
    title: {
      type: String,
      required: true,
    },

    icon: {
      type: String,
      default: '',
    },

    color: {
      type: String,
      default: 'blue-grey-8',
    },

    borderColor: {
      type: String,
      default: '#616161',
    },
  },
};
</script>

<style scoped>

</style>
