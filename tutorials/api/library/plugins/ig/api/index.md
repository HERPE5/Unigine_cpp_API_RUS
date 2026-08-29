# IG Plugin API

> **Warning:** Функциональность, описанная в этой статье, недоступна в редакции Community SDK.
> Для её использования следует перейти на редакцию SDK [**Sim**](https://l.unigine.com/SdhugY462).


Этот раздел содержит неполный набор классов API плагина IG.


IG в UNIGINE спроектирован простым, удобным в использовании и [extensible](../../../../../ig/index.md#extension) благодаря архитектуре на основе плагинов. Основной каркасный плагин, управляющий системами, сущностями, сочленёнными частями, шаблонами компонентов и т.д., — это [IG Plugin](../../../../../api/library/plugins/ig/api/index.md); он работает в терминах движка UNIGINE (*Node, NodeReference* и т.д.) и не привязан к какому-либо конкретному протоколу связи. У плагина IG есть набор дополнительных плагинов, называемых **коннекторами**, которые используются для связывания терминологии IG с терминологией каждого конкретного протокола (например, [CIGI](../../../../../api/library/plugins/ig/cigi/index.md), [HLA](../../../../../api/library/plugins/ig/hla/index.md), [DIS](../../../../../api/library/plugins/ig/dis/index.md)). В целом архитектура выглядит следующим образом:


![IG](../../../../../ig/ig_structure.png)


- [IG::Manager Class](../../../../../api/library/plugins/ig/api/class.managerinterface_cpp.md)
- [IG::ArticulatedPart Class](../../../../../api/library/plugins/ig/api/class.articulatedpart_cpp.md)
- [IG::CollisionSegment Class](../../../../../api/library/plugins/ig/api/class.collisionsegment_cpp.md)
- [IG::CollisionVolume Class](../../../../../api/library/plugins/ig/api/class.collisionvolume_cpp.md)
- [IG::ComponentBaseInterface Class](../../../../../api/library/plugins/ig/api/class.componentbaseinterface_cpp.md)
- [IG::Component Class](../../../../../api/library/plugins/ig/api/class.component_cpp.md)
- [IG::NEDConverter Class](../../../../../api/library/plugins/ig/api/class.nedconverter_cpp.md)
- [IG::Entity Class](../../../../../api/library/plugins/ig/api/class.entity_cpp.md)
- [IG::LightController Class](../../../../../api/library/plugins/ig/api/class.lightcontroller_cpp.md)
- [IG::Meteo Class](../../../../../api/library/plugins/weather/class.meteo_cpp.md)
- [IG::MeteoCameraEffects Class](../../../../../api/library/plugins/weather/class.meteocameraeffects_cpp.md)
- [IG::Region Class](../../../../../api/library/plugins/weather/class.region_cpp.md)
- [IG::SkyMap Class](../../../../../api/library/plugins/weather/class.skymap_cpp.md)
- [IG::Symbol Class](../../../../../api/library/plugins/ig/api/class.symbol_cpp.md)
- [IG::SymbolCircle Class](../../../../../api/library/plugins/ig/api/class.symbolcircle_cpp.md)
- [IG::SymbolText Class](../../../../../api/library/plugins/ig/api/class.symboltext_cpp.md)
- [IG::SymbolPolyline Class](../../../../../api/library/plugins/ig/api/class.symbolpolyline_cpp.md)
- [IG::SymbolsController Class](../../../../../api/library/plugins/ig/api/class.symbolscontroller_cpp.md)
- [IG::SymbolsPlane Class](../../../../../api/library/plugins/ig/api/class.symbolsplane_cpp.md)
- [IG::ViewBase Class](../../../../../api/library/plugins/ig/api/class.viewbase_cpp.md)
- [IG::View Class](../../../../../api/library/plugins/ig/api/class.view_cpp.md)
- [IG::ViewGroup Class](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md)
- [IG::Water Class](../../../../../api/library/plugins/weather/class.water_cpp.md)
- [IG::IGIntersection Structure](../../../../../api/library/plugins/ig/api/class.igintersection_cpp.md)
