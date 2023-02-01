import capparser

alert = capparser.element.Alert(sender="FireTec", 
                                status=capparser.enums.Status.Actual,
                                msgType=capparser.enums.MsgType.Alert,
                                scope=capparser.enums.Scope.Private)
alert.setSource("FireTec")
alert.addAddress("Radio Renascença")

info = capparser.element.Info(category=[capparser.enums.Category.Fire],
                        event="Incendio Florestal em Sever do Vouga",
                        urgency=capparser.enums.Urgency.Immediate,
                        severity=capparser.enums.Severity.Severe,
                        certainty=capparser.enums.Certainty.Observed)
info.setSenderName("FireTec")
info.setInstruction("Foi detetado um possivel incendio florestal na sua area, precaucao e aconselhada.")

param1 = capparser.element.Parameter(parameterName="PS", 
                                     parameterValue="PS=Radio Renascença")
param2 = capparser.element.Parameter(parameterName="PI",
                                     parameterValue="PI=80XX")
param3 = capparser.element.Parameter(parameterName="AF",
                                     parameterValue="AF=95.0")
param4 = capparser.element.Parameter(parameterName="AF",
                                     parameterValue="AF=100.0")
param5 = capparser.element.Parameter(parameterName="AF",
                                     parameterValue="AF=105.0")

info.addParameter(param1)
info.addParameter(param2)
info.addParameter(param3)
info.addParameter(param4)
info.addParameter(param5)

alert.addInfo(info)

capparser.deparse(alert)