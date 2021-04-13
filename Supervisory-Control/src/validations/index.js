/* eslint-disable */

const emailPattern = /^(?=[a-zA-Z0-9@._%+-]{6,254}$)[a-zA-Z0-9._%+-]{1,64}@(?:[a-zA-Z0-9-]{1,63}\.){1,8}[a-zA-Z]{2,63}$/;
const cpfPattern = /^\d{3}.\d{3}.\d{3}-\d{2}$/;
const cnpjPattern = /^\d{2}.\d{3}.\d{3}\/\d{4}-\d{2}$/;
const cepPattern = /^\d{3}.\d{3}.\d{3}-\d{2}$/;
const phonePattern = /^\(\d{2}\) \d{5}-\d{4}$/;
const commercialPhonePattern = /^\(\d{2}\) \d{4}-\d{4}$/;

export const verifyEmail = (val) => emailPattern.test(val) || 'Por favor, digite um endereço de e-mail válido.';
export const verifyCPF = (val) => cpfPattern.test(val) || 'Por favor, digite um CPF válido.';
export const verifyCNPJ = (val) => cnpjPattern.test(val) || 'Por favor, digite um CNPJ válido.';
export const verifyCEP = (val) => cepPattern.test(val) || 'Por favor, digite um CEP válido.';
export const verifyPhone = (val) => phonePattern.test(val) || 'Por favor, digite um número de telefone válido.';
export const verifyCommercialPhone = (val) => commercialPhonePattern.test(val) || 'Por favor, digite um telefone comercial válido.';

export const required = (val) => (!!val && val.trim().length > 0) || 'Este campo é obrigatório';
export const present = (val) => !!val || 'Este campo é obrigatório';
export const requiredIf = (val, otherVal) => {
  if (otherVal) {
    if (val > 0) { return true; } return 'Este campo é obrigatório';
  }
  return true;
};

export const maxLength = (val, maxValue, msg) => val.length <= maxValue || (msg || `Este campo deve ser menor que ${maxValue} caracteres.`);
export const minLength = (val, minValue, msg) => val.length >= minValue || (msg || `Este campo deve ser maior que ${minValue} caracteres.`);
export const equalsTo = (val, otherVal, otherField) => val === otherVal || `Este campo deve ser igual ao campo ${otherField}`;
export const notGreaterThan = (val) => Number(val) < 1000000000 || 'Por favor, digite um valor menor que 1 bilhão.';
export const notLesserThan = (val) => Number(val) > 0 || 'Por favor, digite um valor maior que zero.';
export const dateStart = (val, end) => new Date(val) < new Date(end) || 'A data de início deve anteceder a data de encerramento';
export const dateEnd = (val, start) => new Date(val) > new Date(start) || 'A data de encerramento deve ser posterior à data de encerramento';
export const isCPFValid = (strCPF) => {
  let Soma;
  let Resto;
  Soma = 0;
  if (strCPF === '00000000000') return false;

  for (let i = 1; i <= 9; i++) Soma += parseInt(strCPF.substring(i - 1, i)) * (11 - i);
  Resto = (Soma * 10) % 11;

  if ((Resto === 10) || (Resto === 11)) Resto = 0;
  if (Resto !== parseInt(strCPF.substring(9, 10))) return 'O CPF deve ser válido.';

  Soma = 0;
  for (let i = 1; i <= 10; i++) Soma += parseInt(strCPF.substring(i - 1, i)) * (12 - i);
  Resto = (Soma * 10) % 11;

  if ((Resto === 10) || (Resto === 11)) Resto = 0;
  if (Resto !== parseInt(strCPF.substring(10, 11))) return 'O CPF deve ser válido.';
  return true;
};
