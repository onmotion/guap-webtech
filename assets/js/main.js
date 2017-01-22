/**
 * Created by a.kozhevnikov on 21/01/2017.
 */
window.onload = function () {

    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");

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
                    var ctx = canvas.getContext("2d");
                    ctx.beginPath();
                    ctx.fillStyle = '#fff';
                    ctx.arc(node.xPos, node.yPos + 50, 20, 0, 2 * Math.PI, false);
                    ctx.strokeStyle = '#003';
                    ctx.fill();
                    ctx.stroke();
                    ctx.fillStyle = '#333';
                    ctx.fillText(node.num, node.xPos - 3, node.yPos + 50 + 3);
                    ctx.fillText(resolve.city.name, node.xPos - 10, node.yPos + 25);
                    return resolve.num;
                }).then((n) => {
                    return request('getNodeCon', n).then((connection) => {
                        connections[n] = connection;
                    });
                })
            }))
        }
        $.when.apply(this, promises).then((resolve) => {
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

    const table = $('#routes');
    $(document).on('submit', '#searchForm', function (e) {
        e.preventDefault();
        const cityNmbr = parseInt($(this).find('#select-city').val());
        if (cityNmbr < 0 || cityNmbr > cities.length - 1) return false;

        var citiesArr = cities;

        var promises = [];
        citiesArr.forEach(function (city, i) {
            if(i == cityNmbr) return;
            promises.push(request('getRoutes', [cityNmbr, i]).then((route) => {
                routes[i] = route;
                var path = '';
                $.each(route, function(index, value) {
                    if (index == 1){
                        path = cities[value].name;
                        return;
                    }
                    if (value == -1){
                        return false;
                    }
                    path += ' -> ' + cities[value].name;
                });

                table.append(
                    `<tr>
                        <td>${cities[i].name}</td>
                        <td>${route.pcName}</td>
                        <td>${route.osName}</td>
                        <td>${route.tripPrice} км</td>
                        <td>${path}</td>

                    </tr>`)
            }))
        });
        $.when.apply(this, promises).then((resolve) => {

        })

    });
};