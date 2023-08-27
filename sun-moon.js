module.exports = lib => {
    return {
        calculateMoonStats: (location, date) => {
            if(!location || !location.lon || !location.lat) {
                throw new TypeError('Location must be in Geo format');
            }
            if(!date instanceof Date) {
                throw new TypeError('date must be a Date');
            }
            
            location = {
                height: 0,
                ...location,
            }
            date = {
                year: date.getUTCFullYear(),
                month: date.getUTCMonth() + 1,
                day: date.getUTCDate(),
                hour: date.getUTCHours(),
                minute: date.getUTCMinutes(),
                second: date.getUTCSeconds(),
            };

            return lib.calculateMoonStats(location, date);
        }
    };
}
