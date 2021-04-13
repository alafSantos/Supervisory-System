<template>
  <div class="row">
    <!-- Login -->
    <q-card class="login-card">
      <q-card-section
        class="bg-primary text-white flex justify-center"
      >
        <div class="text-h6">Supervisory Control</div>
      </q-card-section>

      <q-separator />

      <q-card-section>
        <q-form
          @submit="checkUser"
          class="q-gutter-md q-mx-sm"
        >
          <q-input
            class="q-mt-lg"
            v-model="email"
            label="Usuário"
            lazy-rules
            debounce="1000"
          >
            <template v-slot:before>
              <q-icon name="fas fa-fw fa-user" size="sm" />
            </template>
          </q-input>

          <q-input
            type="password"
            v-model="password"
            label="Senha"
            lazy-rules
            debounce="1000"
          >
            <template v-slot:before>
              <q-icon name="fas fa-fw fa-lock" size="sm" />
            </template>
          </q-input>

          <div class="flex justify-center">
            <q-btn
              label="Entrar"
              type="submit"
              color="primary"
            />
          </div>
        </q-form>
      </q-card-section>
    </q-card>
  </div>
</template>

<script>
export default {
  name: 'Login',
  data() {
    return {
        email: null,
        password: null,
        retriveDialog: false,

    };
  },
  methods: {
    checkUser() {
      var done = 0;
      const { email, password } = this;
      console.log(email, password);

      /*
      usuarioX - usuarioXpo00
      alaf - alafpo01
      flavia - flaviapo02
      rebeca - rebecapo03
      vinicius - viniciuspo04*/

      if (email == "alaf" && password =="alafpo01")
      {
        console.log('ALAF ON');
        window.location = "user:"+"Alaf";
        this.$router.push({ name: 'MD1' });
        done=1;
      }
      if (email == "usuarioX" && password =="usuarioXpo00")
      {
        console.log('USUARIOX ON');
        this.$router.push({ name: 'MD1' });
        done=1;
      }
      if (email == "flavia" && password == "flaviapo02") {
        console.log('FLAVIA ON');
        this.$router.push({ name: 'MD1' });
        done = 1;
      }
      if (email == "rebeca" && password =="rebecapo03")
      {
        console.log('REBECA ON');
        this.$router.push({ name: 'MD1' });
        done=1;
      }
      if (email == "vinicius" && password == "viniciuspo04") {
        console.log('VINICIUS ON');
        this.$router.push({ name: 'MD1' });
        done = 1;
      }
      if (done==0)
        alert("error: try again");
    },
  },
};
</script>

<style lang="scss" scoped>
  .login-card {
    width: 50vw;
    min-width: 280px;
    max-width: 500px;
  }
</style>
