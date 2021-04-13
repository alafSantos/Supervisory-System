<script>
import { QTable, exportFile } from 'quasar';

// Função para exportar aquivos .csv
function wrapCsvValue(val, formatFn) {
  let formatted = formatFn !== undefined
    ? formatFn(val)
    : val;

  formatted = formatted === undefined || formatted === null
    ? ''
    : String(formatted);

  formatted = formatted.split('"').join('""');
  /**
   * Excel accepts \n and \r in strings, but some other CSV parsers do not
   * Uncomment the next two lines to escape new lines
   */
  // .split('\n').join('\\n')
  // .split('\r').join('\\r')

  return `"${formatted}"`;
}

export default {
  name: 'Table',
  extends: QTable,
  props: {
    'virtual-scroll': {
      type: Boolean,
      default: true,
    },
    'rows-per-page-label': {
      type: String,
      default: 'Número de resultados por página:',
    },
    'no-data-label': {
      type: String,
      default: 'Sem resultados encontrados.',
    },
    'no-results-label': {
      type: String,
      default: 'Não foi possível encontrar resultados a partir da sua pesquisa.',
    },
    rowKey: {
      type: String,
      default: '_id',
    },
  },
  methods: {
    exportTable() {
      // naive encoding to csv format
      const content = [this.columns.map((col) => wrapCsvValue(col.label))].concat(
        this.data.map((row) => this.columns.map((col) => wrapCsvValue(
          typeof col.field === 'function'
            ? col.field(row)
            : row[col.field === undefined ? col.name : col.field],
          col.format,
        )).join(',')),
      ).join('\r\n');

      const status = exportFile(
        'table-export.csv',
        content,
        'text/csv',
      );

      if (status !== true) {
        this.$q.notify({
          message: 'O download do arquivo .csv foi bloqueado pelo seu browser...',
          color: 'negative',
          icon: 'warning',
        });
      }
    },
  },
};
</script>

<style lang="sass" scoped>
</style>
