import { Loading, QSpinnerGears } from 'quasar';

Loading.setDefaults({
  delay: 250,
  message: 'Carregando...',
  messageColor: 'white',
  spinnerSize: 140,
  spinner: QSpinnerGears,
});
