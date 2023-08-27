let lib = require('bindings')('sun-moon-almanac');

module.exports = {
    sunMoon: require('./sun-moon')(lib),
}
