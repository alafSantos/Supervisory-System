<template>
  <q-page class="row q-ma-sm">
    <div class="col-12">
      <div class="row">
        <div class="col-12" style="text-align: center">
          <q-btn :color="this.getColorNot()" @click="showNotif" :label="this.getErroLabel()" />
        </div>
        <div class="col-xs-12 col-sm-6 col-md-3 q-pa-sm">
          <CardBadge title='Temperatura'
                     borderColor="#00ff00"
                     color="primary">
            <template v-slot:content>
              <div class="text-h5 text-black">
                {{ getTemperatura }}°C
              </div>
            </template>
          </CardBadge>
        </div>

        <div class="col-xs-12 col-sm-6 col-md-3 q-pa-sm">
          <CardBadge title='Umidade'
                     borderColor="#00ff00"
                     color="primary">
            <template v-slot:content>
              <div class="text-h5 text-black">
                {{ getUmidade }}%
              </div>
            </template>
          </CardBadge>
        </div>
      </div>
    </div>
  </q-page>
</template>

<script>
  import CardBadge from 'components/cardBadge';
  import LineChart from 'components/charts/lineChart';
  import Container from 'components/container';

  export default {
    name: 'MD9',
    components: {
      CardBadge,
      LineChart,
      Container,
    },
    data() {
      return {
        temperatura: 0,
        umidade: 0,
        erro: 0,
      };
    },
    computed: {
      getTemperatura() {
        if (String(this.temperatura) == "-127") return "erro";
        else return `${this.temperatura}`;
      },
      getUmidade() {
        if (String(this.umidade) == "-127") return "erro";
        else return `${this.umidade}`;
      },
    },
    methods: {
      getCaption() {
        switch (this.erro) {
          case 0:
            return 'Verifique sua conexão com a internet.\nSe demorar muito, o sistema pode estar offline.'
            break;
          case 1:
            return 'Há alguém';
            break;
          case 2:
            return 'Temperatura: ' + this.temperatura + '°C';
            break;
          case 3:
            return 'Umidade: ' + this.umidade + '%';
            break;
          default:
            return 'Não te preocupes';
        }
      },
      getErroLabel() {
        switch (this.erro) {
          case 0:
            return 'Carregando Dados';
            break;
          case 1:
            return 'Erro na Temperatura';
            break;
          case 2:
            return 'Erro na Umidade';
            break;
          default:
            return 'Tudo ok :)';
        }
      },
      getColorNot() {
        //https://quasar.dev/style/color-palette#Color-List
        switch (this.erro) {
          case 0:
            return 'grey';
          case 1:
            return 'pink-13';
            break;
          case 2:
            return 'deep-orange';
            break;
          case 3:
            return 'orange';
            break;
          default:
            return 'black';
        }
      },
      showNotif() {
        this.$q.notify({
          message: this.getErroLabel(),
          color: this.getColorNot(),
          caption: this.getCaption(),
        });
      },
      handleData() {
        async function getData() {
          let valuesJSON = [];
          const json_url = 'https://cors-anywhere.herokuapp.com/http://7345653d8e71.ngrok.io; //https://api.jsonbin.io/b/5ee79d3c0e966a7aa369f1f5';//'file:///home/alaf/md1.html'; //'http://192.168.0.105:8081/';
          const response = await fetch(json_url);
          const datajson = await response.json();
          valuesJSON = [datajson.TempDHT22, datajson.UmidDHT22, datajson.pir];
          return valuesJSON;
        }
        let jsonV = getData();
        console.log(jsonV);
        const promise = new Promise((resolve, reject) => {
          setTimeout(() => {
            resolve(jsonV);
          }, null);
        });
        promise.then(jsonV => {
          //alert(message);
          this.temperatura = jsonV[0];
          this.umidade = jsonV[1];
          if (this.temperatura > 60) this.erro = 1; //pensar nos casos criticos de temperatura e umidade, dai substituir nos ifs
          else if (this.umidade > 40) this.erro = 2;
          else this.erro = 4;
        });
      },
    },
    async created() {
      this.handleData();
    },
  };
</script>

<style lang="scss" scoped>
</style>
