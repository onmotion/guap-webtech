/**
 * Created by a.kozhevnikov on 21/01/2017.
 */
window.onload = function () {

    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");
    var canvas2 = document.getElementById("canvas2");
    var ctx2 = canvas2.getContext("2d");
    var canvas3 = document.getElementById("canvas3");
    var ctx3 = canvas3.getContext("2d");

    function request(type, param) {
        return new Promise(function (resolve, reject) {
            $.ajax({
                type: 'get',
                url: '/index.php',
                dataType: 'json',
                data: {
                    'type': type,
                    'param': param
                },
                success: function (response) {
                    resolve(response);
                },
                error: function (xhr, textStatus, errorThrown) {
                    console.log(textStatus);
                    reject(textStatus);
                }
            });

        });
    }

    var cities = [],
        connections = [],
        nodes = [],
        routes = [];
    const $citiesList = $('#citiesList ul');
    const $selectCity = $('#select-city');
    //получаем количество городов
    request('getCityNum').then(function (resolve) {
        $('#numOfCities').html(resolve.quantity);
        var promises = [];
        for (var i = 0; i < resolve.quantity; i++) {
            const n = i;
            //получаем названия городов
            promises.push(request('getCityName', i).then((resolve) => {
                cities[n] = resolve;
                return {num: n, city: resolve};
            }).then((resolve) => {
                return request('getSimpleNode', resolve.num).then((node) => {
                    nodes[resolve.num] = node;
                    var nLength = node.num.toString().length;
                    ctx3.beginPath();
                    ctx3.fillStyle = '#fff';
                    ctx3.arc(node.xPos, node.yPos + 50, 15, 0, 2 * Math.PI, false);
                    ctx3.strokeStyle = '#003';
                    ctx3.fill();
                    ctx3.stroke();
                    ctx3.fillStyle = '#333';
                    ctx3.font = '11pt Calibri';
                    ctx3.fillText(node.num, node.xPos - 4 * nLength, node.yPos + 50 + 4);
                    ctx3.fillText(resolve.city.name, node.xPos - 10, node.yPos + 25);
                    return resolve.num;
                }).then((n) => {
                    return request('getNodeCon', n).then((connection) => {
                        connections[n] = connection;
                    });
                })
            }))
        }
        $.when.apply(this, promises).then((resolve) => {
            ctx.strokeStyle = '#999';
            connections.forEach(function (connection, i) {
                for (var relCity in connection) {
                    if (connection.hasOwnProperty(relCity)) {
                        if (connection[relCity] != -1) {
                            ctx.globalCompositeOperation = 'destination-over';
                            ctx.beginPath();
                            ctx.moveTo(nodes[i]['xPos'], nodes[i]['yPos'] + 50);
                            ctx.lineTo(nodes[connection[relCity]]['xPos'], nodes[connection[relCity]]['yPos'] + 50);
                            ctx.stroke();
                        }
                    }
                }

            });
            cities.forEach(function (city, n) {
                $citiesList.append(`<li>${n} - ${city.name}</li>`);
                $selectCity.append(`<option value=${n}>${city.name}</option>`);
            });
        })
    });

    const table = $('#routes tbody');
    $(document).on('submit', '#searchForm', function (e) {
        e.preventDefault();
        table.html('');
        const cityNmbr = parseInt($(this).find('#select-city', 10).val());
        if (cityNmbr < 0 || cityNmbr > cities.length - 1) return false;

        var citiesArr = cities;

        var promises = [];
        citiesArr.forEach(function (city, i) {
            if(i == cityNmbr) return;
            promises.push(request('getRoutes', [cityNmbr, i]).then((route) => {
                if (route === null){
                    table.append(
                        `<tr>
                        <td>${cities[i].name}</td>
                        <td>-</td>
                        <td>-</td>
                        <td>-</td>
                        <td>маршрут еще никто не нашел...</td>
                        <td></td>
                    </tr>`);
                    return;
                }
                routes[i] = route;
                var path = '';
                var pathNums = '';
                $.each(route, function(index, value) {
                    if (index == 1){
                        path = cities[value].name;
                        pathNums = value;
                        return;
                    }
                    if (value == -1){
                        return false;
                    }
                    path += ' > ' + cities[value].name;
                    pathNums += ';' + value;
                });

                table.append(
                    `<tr>
                        <td>${cities[i].name}</td>
                        <td>${route.pcName}</td>
                        <td>${route.osName}</td>
                        <td>${route.tripPrice} км</td>
                        <td>${path}</td>
                        <td><a class="drawRoute" href="#" data-value="${pathNums}"><i class="icon-eye"></i></a></td>
                    </tr>`)
            }))
        });
        $.when.apply(this, promises).then((resolve) => {

        });
        return false;
    });

    $(document).on('click', '.drawRoute', function (e) {
        e.preventDefault();
        const value = $(this).attr('data-value');
        const routes = value.split(';');
        var p = new Promise((resolve, reject) => {
            $('html, body').animate({
                scrollTop: 0
            }, 500);
            setTimeout(function () {
                resolve(true);
            }, 1000);

        });
        ctx2.clearRect(0, 0, canvas.width, canvas.height);
        ctx2.lineWidth = 2;
        var gLevel = 0;
        var bLevel = 255;
        routes.forEach(function (city, i) {
            const n = city;
            p = p.then((resolve) => {
                return new Promise((resolve) => {
                    gLevel += parseInt(255 / routes.length, 10);
                    bLevel -= parseInt(255 / routes.length, 10);
                    ctx2.strokeStyle = `rgb(0,${gLevel},${bLevel})`;
                    if(i > 0) {
                        ctx2.lineTo(nodes[n]['xPos'], nodes[n]['yPos'] + 50);
                        ctx2.stroke();
                    }
                    ctx2.beginPath();
                    ctx2.moveTo(nodes[n]['xPos'], nodes[n]['yPos'] + 50);
                    setTimeout(function () {
                        resolve (true);
                    }, 500);
                })

            })
        });
        $.when(p).then((resolve) => {
            console.log('done');
        });

    });

    $(document).on('click', '#reset', function (e) {
        e.preventDefault();
        request('reset').then((resolve) => {
            alert('Вычисления сброшены.');
        });
    });
};