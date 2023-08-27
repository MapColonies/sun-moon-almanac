const assert = require('assert')
const fs = require('fs')
const path = require('path')

const { sunMoon } = require('../index');

function assertAlmostZero(difference, epsilon, message) {
    assert(Math.abs(difference) <= Math.abs(epsilon), message);
}

function asyncLoadFile(fileName) {
    return new Promise((resolve, reject) => fs.readFile(fileName, (error, res) => error ? reject(error) : resolve(res)));
}

function partition(array, n) {
    return array.length ? [array.splice(0, n)].concat(partition(array, n)) : [];
}

function testAndCompare(location, date, elevation, azimuth, illuminationPercentage) {
    const result = sunMoon.calculateMoonStats(location, date);
    assertAlmostZero(
        result.elevation - elevation,
        1,
        `Elevation mismatch: on date (${date}), got ${result.elevation} but expected ${elevation}`,
    );
    const azimuthDist = Math.abs((result.azimuth % 360) - (azimuth % 360) % 360);
    assertAlmostZero(
        Math.min(azimuthDist, 360 - azimuthDist),
        1.4,
        `Azimuth mismatch: on date (${date}), got ${result.azimuth} but expected ${azimuth}`,
    );
    assertAlmostZero(
        result.illuminationPercentage - illuminationPercentage,
        1,
        `Illumination mismatch: on date (${date}), got ${result.illuminationPercentage} but expected ${illuminationPercentage}`,
    );
}

async function loadFile(fileName) {
    const csv = await asyncLoadFile(path.resolve(__dirname, fileName));
    const lines = csv.toString().split('\n').map(line => line.split(','));

    const location = JSON.parse(lines.splice(0, 1));
    const headers = lines.splice(0, 1)[0].reduce((acc, header, index) => ({ ...acc, [header.toLowerCase().replace('\r', '')]: index }), {});

    return { lines, location, headers };
}

// TODO: fix the tests - remove the timeout
describe('MoonSun tests', () => {
    it('Should fit the csv for 2019-2020', async () => {
        const { lines, location, headers } = await loadFile('moon sun data.csv');
        describe('run tests', () => {
            const parts = partition(lines, 10000);
            for (const part in parts) {
                it(`Should work for part ${Number(part) + 1} of ${parts.length}`, () => {
                    for (const line of parts[part]) {
                        if (line.length < Object.keys(headers).length) {
                            continue;
                        }
                        const date = new Date(Date.UTC(line[headers.year], line[headers.month] - 1, line[headers.day], line[headers.hour], line[headers.minute]));
                        testAndCompare(location, date, line[headers.alt], line[headers.az], line[headers.fm]);
                    }
                });
            }
        });
    });


    it('Should fit the csv for 28/11/2018', async () => {
        const { lines, location, headers } = await loadFile('moon sun data2.csv');
        describe('run tests', () => {
            it(`Should work for 28/11/2018`, () => {
                for (const line of lines) {
                    if (line.length < Object.keys(headers).length) {
                        continue;
                    }
                    const date = new Date(line[headers.year], line[headers.month] - 1, line[headers.day], line[headers.hour], line[headers.minute]);
                    testAndCompare(location, date, line[headers.alt], line[headers.az], line[headers.fm]);
                }
            });
        });
    });
});
