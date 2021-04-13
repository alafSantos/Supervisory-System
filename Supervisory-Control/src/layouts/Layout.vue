<template>
  <q-layout view="LHh lpR lFf">
    <q-header reveal elevated class="bg-primary text-white">
      <q-toolbar>
        <q-btn dense flat round icon="menu" @click="drawer = !drawer" />
        <q-toolbar-title>
          {{ pageTitle }}
        </q-toolbar-title>
      <q-space />
      <div class="q-pa-md">
      <q-btn
        color="primary"
        @click="$q.fullscreen.toggle()"
        :icon="$q.fullscreen.isActive ? 'fullscreen_exit' : 'fullscreen'"
        :label="$q.fullscreen.isActive ? 'ON' : 'OFF'"
      />
      </div>      
            <div class="row items-center no-wrap">
            </div>
      </q-toolbar>
    </q-header>

    <q-drawer
      show-if-above
      v-model="drawer"
      side="left"
      :width="300"
      :breakpoint="750"
      elevated
      content-class="bg-primary"
    >
      <q-scroll-area class="fit">
        <q-list>
          <q-item
            class="text-center bg-9 q-pa-lg"
          >
            <q-item-section>
              <div class="text-h4 text-white">
                <q-btn color="primary" label="Supervisório">
                  <q-tooltip
                    transition-show="rotate"
                    transition-hide="rotate"
                  >
                    Escolha um Host
                  </q-tooltip>
                </q-btn>
              </div>
            </q-item-section>
          </q-item>
          <DrawerLink
            v-for="link in drawerLinks"
            :key="link.title"
            v-bind="link"
          />
        </q-list>
      </q-scroll-area>
    </q-drawer>

    <q-page-container>
      <router-view />
    </q-page-container>

    <q-footer elevated class="bg-grey-8 text-white">
      <q-toolbar>
        <q-toolbar-title>
          <div class="text-subtitle1">
            {{ branding }}
          </div>
        </q-toolbar-title>
        <q-space />
      </q-toolbar>
    </q-footer>

  </q-layout>
</template>

<script>
import { date } from 'quasar';
import DrawerLink from 'components/drawerLink';
export default {
  name: 'Layout',
  components: {
    DrawerLink,
  },
  data() {
    return {
      projectName: 'SCT500',
      drawer: false,
      drawerLinks: [
        {
          title: 'MD1',
          icon: 'filter_1',
          link: { name: 'MD1' },
        },
        {
          title: 'MD2',
          icon: 'filter_2',
          link: { name: 'MD2' },
        },
        {
          title: 'MD3',
          icon: 'filter_3',
          link: { name: 'MD3' },
        },
        {
          title: 'MD4',
          icon: 'filter_4',
          link: { name: 'MD4' },
        },
        {
          title: 'MD5',
          icon: 'filter_5',
          link: { name: 'MD5' },
        },
        {
          title: 'MD6',
          icon: 'filter_6',
          link: { name: 'MD6' },
        },
        {
          title: 'MD7',
          icon: 'filter_7',
          link: { name: 'MD7' },
        },
        {
          title: 'MD8',
          icon: 'filter_8',
          link: { name: 'MD8' },
        },
        {
          title: 'MD9',
          icon: 'filter_9',
          link: { name: 'MD9' },
        },
       ],
    };
  },
  computed: {
    branding() {
      const year = date.formatDate(Date.now(), 'YYYY');
      return `${this.projectName} ©${year}`;
    },
    pageTitle() {
      switch(this.$store.getters['MainStore/getScreen']) {
        case "MD1":
          return "MD1"
          break;
        case "MD2":
          return "MD2"
          break;
        case "MD3":
          return "MD3"
          break;
        case "MD4":
          return "MD4"
          break;
        case "MD5":
          return "MD5"
        case "MD6":
          return "MD6"
          break;
        case "MD7":
          return "MD7"
          break;
        case "MD8":
          return "MD8"
          break;
        case "MD9":
          return "MD9"
          break;
        default:
          return "ERROR UNKNOWN"
      }
    },
  }
};
</script>

<style lang="scss" scoped>
</style>
