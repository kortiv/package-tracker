#include "interface_adapters/answer_presenter.h"
#include "interface_adapters/track_package_presenter.h"

#include <cassert>

void track_presenter_maps_the_package_response_to_its_view_model() {
    interface_adapters::TrackPackagePresenter presenter;

    presenter.present(use_cases::TrackPackageOutputData{
        "PKG-401",
        "In Transit"});

    const auto& view_model = presenter.latest_view_model();
    assert(view_model.has_value());
    assert(view_model->tracking_number == "PKG-401");
    assert(view_model->status == "In Transit");
}

void answer_presenter_preserves_human_escalation_for_the_view() {
    interface_adapters::AnswerPresenter presenter;

    presenter.present(use_cases::AnswerOutputData{
        {},
        true,
        "Model response violated policy"});

    const auto& view_model = presenter.latest_view_model();
    assert(view_model.has_value());
    assert(view_model->requires_human_review);
    assert(view_model->escalation_reason == "Model response violated policy");
}

int main() {
    track_presenter_maps_the_package_response_to_its_view_model();
    answer_presenter_preserves_human_escalation_for_the_view();
}
