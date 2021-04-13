<template>
  <div id="container" />
</template>

<script>
// eslint-disable-next-line
import tableau from 'tableau-api';

export default {
  name: 'Tableau',
  props: {
    url: {
      type: String,
      required: true,
    },
    options: {
      type: Object,
      default: () => ({
        hideTabs: true,
        onFirstInteractive: () => {
          console.log('Run this code when the viz has finished loading.');
        },
      }),
    },
  },
  mounted() {
    const container = document.getElementById('container');
    const { url, options } = this;
    // eslint-disable-next-line
    new window.tableau.Viz(container, url, options);
  },
};
</script>

<style lang="scss" scoped>

</style>
